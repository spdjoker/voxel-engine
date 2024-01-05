#include "fmt/core.h"
// #include "jkr/components/camera.hpp"
// #include "jkr/components/transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "jkr/engine/application.hpp"
#include "jkr/engine/input_enums.hpp"
#include "jkr/graphics/objects/ebo.hpp"
#include "jkr/graphics/objects/vao.hpp"
#include "jkr/graphics/objects/vbo.hpp"
#include "jkr/graphics/shader.hpp"
#include "jkr/types/common.hpp"
// #include "jkr/graphics/texture.hpp"
// #include "jkr/util/event_flags.hpp"
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
  vec3 flatColor(0.0f, 1.0f, 0.0f);

  vec3 camera_pos = vec3(0.0f, 0.0f, 3.0f);
  vec3 camera_dir = vec3(0.0f, 0.0f, -1.0f);
  vec3 world_up = vec3(0.0f, 1.0f, 0.0f);

  mat4 view_matrix = glm::lookAt(camera_pos, camera_pos + camera_dir, world_up);

  float fov = 45.0f;
  float aspectRatio = (float)app.windowSize().x / (float)app.windowSize().y;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  mat4 proj_matrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

  mat4 camera_matrix = proj_matrix * view_matrix;
  float camera_speed = 5.0f;
  char camera_update = 0;
  vec2 camera_vel(0.0f, 0.0f);

  while (app.running()) {
    app.clear();
    app.poll();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    if (app.input().onKey(KeyCode::S)) {
      camera_vel.y += 1;
      camera_update |= 1;
    }
    if (app.input().onKey(KeyCode::W)) {
      camera_vel.y -= 1;
      camera_update |= 1;
    }
    if (app.input().onKey(KeyCode::A)) {
      camera_vel.x -= 1;
      camera_update |= 1;
    }
    if (app.input().onKey(KeyCode::D)) {
      camera_vel.x += 1;
      camera_update |= 1;
    }
    if (app.input().onKey(KeyCode::SPACE)) {
      camera_pos.y += camera_speed * app.deltaTime();
      fmt::println("{}",camera_pos.y);
      camera_update |= 2;
    }
    if (app.input().onKey(KeyCode::LEFT_SHIFT)) {
      camera_pos.y -= camera_speed * app.deltaTime();
      fmt::println("{}",camera_pos.y);
      camera_update |= 2;
    }
    if (camera_update) {
      if (camera_update & 1) {
        camera_vel = glm::normalize(camera_vel) * camera_speed * app.deltaTime();
        camera_pos.x += camera_vel.x;
        camera_pos.z += camera_vel.y;
        camera_vel = vec2(0.0f, 0.0f);
      }
      view_matrix = glm::lookAt(camera_pos, camera_pos + camera_dir, world_up);
      camera_matrix = proj_matrix * view_matrix;
      camera_update = 0;
    }

    flatShader.activate();
    flatShader.setUniformMat4(uCameraMatrix, camera_matrix);
    flatShader.setUniformVec3f(uColor, flatColor);

    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    app.render();
  }

  app.clean();

  return 0;
}
