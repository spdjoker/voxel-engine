#include <fmt/core.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "jkr/components/camera.hpp"
#include "jkr/components/transform.hpp"
#include "jkr/engine/application.hpp"
#include "jkr/engine/input_enums.hpp"
#include "jkr/graphics/objects/ebo.hpp"
#include "jkr/graphics/objects/vao.hpp"
#include "jkr/graphics/objects/vbo.hpp"
#include "jkr/graphics/shader.hpp"
#include "jkr/types/common.hpp"
#include <GL/glew.h>
#include <iostream>

int main() {
  Application app;
  app.init("My Application", 800, 600);

  // app.init("My Fullscreen Application");

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  vec3 vertices[] = {
    vec3(-0.5f, -0.5f,  0.0f),    // Vertex 0     3-----2
    vec3( 0.5f, -0.5f,  0.0f),    // Vertex 1     | CCW |
    vec3( 0.5f,  0.5f,  0.0f),    // Vertex 2     |  T  |
    vec3(-0.5f,  0.5f,  0.0f)     // Vertex 3     0-----1
  };

  unsigned int indices[] = {
    0, 1, 2, 0, 2, 3
  };

  VAO::Create(vao);
  VAO::Bind(vao);
  VBO::Create(vbo, vertices, sizeof(vertices));
  EBO::Create(ebo, indices, sizeof(indices));

  // Flat Vertex Data
  VAO::LinkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(vec3), (void*)0);
  
  Shader flatShader("resources/shaders/flat-vert.glsl", "resources/shaders/flat-frag.glsl");
  flatShader.activate();
  int uColor = flatShader.getUniform("uColor");
  int uCameraMatrix = flatShader.getUniform("uCameraMatrix");
  int uModelMatrix = flatShader.getUniform("uModelMatrix");

  vec3 camera_pos = vec3(0.0f, 0.0f, -3.0f);
  vec3 camera_dir = vec3(0.0f, 0.0f, 1.0f);
  vec3 world_up = vec3(0.0f, 1.0f, 0.0f);

  mat4 view_matrix = glm::lookAtLH(camera_pos, camera_pos + camera_dir, world_up);

  float fov = 45.0f;
  float aspectRatio = (float)app.windowSize().x / (float)app.windowSize().y;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  mat4 proj_matrix = glm::perspectiveLH(fov, aspectRatio, nearPlane, farPlane);

  enum CAMERA_MOVEMENT {
    TRANSLATE_X   = 1,
    TRANSLATE_Y   = 2,
    TRANSLATE_Z   = 4,
    TRANSLATE_XY  = TRANSLATE_X  | TRANSLATE_Y,
    TRANSLATE_XZ  = TRANSLATE_X  | TRANSLATE_Z,
    TRANSLATE_XYZ = TRANSLATE_XY | TRANSLATE_Z
  };

  float camera_speed = 5.0f;
  flag8 camera_update;
  vec3 camera_velocity(0.0f, 0.0f, 0.0f);

  float tmpf;

  Camera camera(Transform(vec3(1.0f,0.0f,-3.0f)));
  camera.perspective(45.0f, (float)app.windowSize().x / (float)app.windowSize().y, 0.1f, 100.0f);
  Transform transform(vec3(0.0f,0.0f,0.0f));
  vec3 flatColor(0.0f, 1.0f, 1.0f);

  while (app.running()) {
    app.clear();
    app.poll();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    if (app.input().onKey(KeyCode::D)) {
      camera_velocity.x += 1;
      camera_update.toggleSignalFlags(TRANSLATE_X);
    }
    if (app.input().onKey(KeyCode::A)) {
      camera_velocity.x -= 1;
      camera_update.toggleSignalFlags(TRANSLATE_X);
    }
    if (app.input().onKey(KeyCode::SPACE)) {
      camera_velocity.y += 1;
      camera_update.toggleSignalFlags(TRANSLATE_Y);
    }
    if (app.input().onKey(KeyCode::LEFT_SHIFT)) {
      camera_velocity.y -= 1;
      camera_update.toggleSignalFlags(TRANSLATE_Y);
    }
    if (app.input().onKey(KeyCode::W)) {
      camera_velocity.z += 1;
      camera_update.toggleSignalFlags(TRANSLATE_Z);
    }
    if (app.input().onKey(KeyCode::S)) {
      camera_velocity.z -= 1;
      camera_update.toggleSignalFlags(TRANSLATE_Z);
    }
    if (camera_update.hasSignalFlags()) {
      // If both X and Z translations need to happen, normalize the horizontal movement
      if (camera_update.hasAllSignalFlags(TRANSLATE_XZ)) {
        tmpf = camera_velocity.y;
        camera_velocity = glm::normalize(vec3(camera_velocity.x, 0.0f, camera_velocity.z));
        camera_velocity.y = tmpf;
      }
      if (camera_update.hasAnySignalFlags(TRANSLATE_XYZ)) {
        camera.transform().translate(camera_velocity * camera_speed * app.deltaTime());
        camera_velocity = VEC3_ZERO;
      }
      camera_update.processSignalFlags();
    }

    flatShader.activate();

    camera.update();
    flatShader.setUniformMat4(uCameraMatrix, camera.matrix());

    transform.update();
    flatShader.setUniformMat4(uModelMatrix, transform.matrix());
    flatShader.setUniformVec3f(uColor, flatColor);

    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    app.render();
  }

  app.clean();

  return 0;
}
