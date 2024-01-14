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

void information() {
  fmt::print(
    "[  ESC  ] - Close Window\n"
    "\nMovement:\n"
    "[   W   ] - Move Forward (XZ Plane)\n"
    "[   A   ] - Move Left\n"
    "[   S   ] - Move Backward (XZ Plane)\n"
    "[   D   ] - Move Right\n"
    "[ SPACE ] - Move Up (Y-Axis)\n"
    "[L-SHIFT] - Move Up (Y-Axis)\n"
    "\nCamera:\n"
    "[   R   ] - Look Up\n"
    "[   F   ] - Look Down\n"
    "[   Q   ] - Look Left\n"
    "[   E   ] - Look Right\n"
  );
}

int main() {
  Application app;
  app.init("My Application", 800, 600);

  information();

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

  enum CAMERA_MOVEMENT {
    TRANSLATE_X   = 1,
    TRANSLATE_Y   = 2,
    TRANSLATE_Z   = 4,
    TRANSLATE_XY  = TRANSLATE_X  | TRANSLATE_Y,
    TRANSLATE_XZ  = TRANSLATE_X  | TRANSLATE_Z,
    TRANSLATE_XYZ = TRANSLATE_XY | TRANSLATE_Z,
    ROTATE_X      = 8,
    ROTATE_Y      = 16,
    ROTATE_XY     = ROTATE_X | ROTATE_Y
  };

  Camera camera(Transform(vec3(0.0f,0.0f,-3.0f)));
  camera.perspective(45.0f, (float)app.windowSize().x / (float)app.windowSize().y, 0.1f, 100.0f);

  const float camera_move_speed = 8.0f;
  const float camera_rot_speed = 70.0f;

  flag8 move_flags;

  vec3 camera_velocity(0.0f, 0.0f, 0.0f);
  vec3 camera_rotation(0.0f, 0.0f, 0.0f);
  float tmpf;   // Pre-declared float used in main loop to reduce reallocation.

  Transform transform(vec3(0.0f,0.0f,0.0f));
  vec3 flatColor(0.0f, 1.0f, 1.0f);

  while (app.running()) {
    app.clear();
    app.poll();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    if (app.input().onKey(KeyCode::D)) {            // CAMERA RIGHT
      camera_velocity += camera.transform().right();
      move_flags.toggleSignalFlags(TRANSLATE_X);   
    }
    if (app.input().onKey(KeyCode::A)) {            // Inverted CAMERA RIGHT
      camera_velocity -= camera.transform().right();
      move_flags.toggleSignalFlags(TRANSLATE_X);  
    }
    if (app.input().onKey(KeyCode::W)) {            // Projection of CAMERA FORWARD on xz-plane
      camera_velocity += camera.transform().forward();
      camera_velocity.y = 0.0f;
      move_flags.toggleSignalFlags(TRANSLATE_Z);
    }
    if (app.input().onKey(KeyCode::S)) {            // Projection of CAMERA FORWARD on xz-plane
      camera_velocity -= camera.transform().forward();
      camera_velocity.y = 0.0f;
      move_flags.toggleSignalFlags(TRANSLATE_Z);
    }
    if (app.input().onKey(KeyCode::SPACE)) {        // WORLD UP
      camera_velocity += VEC3_UP;
      move_flags.toggleSignalFlags(TRANSLATE_Y);
    }
    if (app.input().onKey(KeyCode::LEFT_SHIFT)) {   // Inverted WORLD UP
      camera_velocity -= VEC3_UP;
      move_flags.toggleSignalFlags(TRANSLATE_Y);
    }
    if (app.input().onKey(KeyCode::E)) {
      camera_rotation.y += camera_rot_speed;
      move_flags.toggleSignalFlags(ROTATE_Y);
    }
    if (app.input().onKey(KeyCode::Q)) {
      camera_rotation.y -= camera_rot_speed;
      move_flags.toggleSignalFlags(ROTATE_Y);
    }
    if (app.input().onKey(KeyCode::F) && camera.transform().getRotation().x < 85.0f) {
      camera_rotation.x += camera_rot_speed;
      move_flags.toggleSignalFlags(ROTATE_X);
    }
    if (app.input().onKey(KeyCode::R) && camera.transform().getRotation().x > -85.0f) {
      camera_rotation.x -= camera_rot_speed;
      move_flags.toggleSignalFlags(ROTATE_X);
    }
    if (move_flags.hasSignalFlags()) {
      // If both X and Z translations need to happen, normalize the horizontal movement
      if (move_flags.hasAnySignalFlags(TRANSLATE_XZ)) {
        tmpf = camera_velocity.y;
        camera_velocity = glm::normalize(vec3(camera_velocity.x, 0.0f, camera_velocity.z));
        camera_velocity.y = tmpf;
      }
      if (move_flags.hasAnySignalFlags(TRANSLATE_XYZ)) {
        camera.transform().translate(camera_velocity * camera_move_speed * app.deltaTime());
        camera_velocity = VEC3_ZERO;
      }
      if (move_flags.hasAnySignalFlags(ROTATE_XY)) {
        camera_rotation.x *= app.deltaTime();
        camera_rotation.y *= app.deltaTime();
        camera_rotation   += camera.transform().getRotation();

        // Clamp pitch to prevent 360s
        if (camera_rotation.x > 88.0f) {
          camera_rotation.x = 88.0f;
        } else if (camera_rotation.x < -88.0f) {
          camera_rotation.x = -88.0f;
        }
        
        camera.transform().setRotation(camera_rotation);
        camera_rotation = VEC3_ZERO;
      }
      move_flags.processSignalFlags();
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
