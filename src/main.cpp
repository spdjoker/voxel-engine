#include "fmt/core.h"
#include "jkr/components/camera.hpp"
#include "jkr/components/transform.hpp"
#include "jkr/engine/application.hpp"
#include "jkr/graphics/objects/ebo.hpp"
#include "jkr/graphics/objects/vao.hpp"
#include "jkr/graphics/objects/vbo.hpp"
#include "jkr/graphics/shader.hpp"
#include "jkr/graphics/texture.hpp"
#include "jkr/types/matrix4.hpp"
#include "jkr/types/quaternion.hpp"
#include "jkr/types/vector2.hpp"
#include "jkr/types/vector3f.hpp"
#include "jkr/util/event_flags.hpp"
#include <GL/glew.h>
#include <iostream>

struct FlatVertex {
  float position[3];
  // float color[3];
  float uv[2];
};
struct ColoredVertex {
  float position[3];
  float color[3];
  float uv[2];
};

int main() {
  Application app;

  app.init("My Application", 800, 600);
  // app.init("My Fullscreen Application");

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  // ColoredVertex vertices[] = {
    // {{-0.5f,  0.0f, -0.5f}, {1.0f,0.0f,0.0f}, { 0.0f,  0.0f}},    // Vertex 0
    // {{-0.5f,  0.0f,  0.5f}, {0.0f,1.0f,0.0f}, { 0.0f, 20.0f}},    // Vertex 1
    // {{ 0.5f,  0.0f,  0.5f}, {0.0f,0.0f,1.0f}, {20.0f, 20.0f}},    // Vertex 2
    // {{ 0.5f,  0.0f, -0.5f}, {1.0f,0.0f,1.0f}, {20.0f,  0.0f}}    // Vertex 3
  // };

  FlatVertex vertices[] = {
    {{-0.5f,  0.0f, -0.5f}, { 0.0f,  0.0f}},    // Vertex 0     3-----2
    {{ 0.5f,  0.0f, -0.5f}, {50.0f,  0.0f}},    // Vertex 1     | CCW |
    {{ 0.5f,  0.0f,  0.5f}, {50.0f, 50.0f}},    // Vertex 2     |  T  |
    {{-0.5f,  0.0f,  0.5f}, { 0.0f, 50.0f}}     // Vertex 3     0-----1
  };

  unsigned int indices[] = {
    0, 1, 2, 0, 2, 3
  };

  Vector3f color(1.0f, 1.0f, 1.0f);
  
  VAO::Create(vao);
  VAO::Bind(vao);
  VBO::Create(vbo, vertices, sizeof(vertices));
  EBO::Create(ebo, indices, sizeof(indices));

  // Colored Vertex Data
  // VAO::LinkAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  // VAO::LinkAttribute(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)offsetof(Vertex,color));
  // VAO::LinkAttribute(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)offsetof(Vertex, uv));
  // Flat Vertex Data
  VAO::LinkAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  VAO::LinkAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)offsetof(FlatVertex, uv));

  
  Shader flatShader("resources/shaders/sprite-vert.glsl", "resources/shaders/sprite-frag.glsl");
  flatShader.activate();
  int uColor = flatShader.getUniform("uColor");
  int uTexture = flatShader.getUniform("uTexture");
  int uModelMatrix = flatShader.getUniform("uModelMatrix");
  int uCameraMatrix = flatShader.getUniform("uCameraMatrix");

  Transform transform({0.0f,0.0f,0.0f}, Vector3f::Zero, Vector3f::One * 50.0f);
  Texture tex("resources/images/gridbox.jpg");

  // Set up the camera
  Camera camera;
  camera.perspective(60.0f, ((float)app.windowSize().getX())/((float)app.windowSize().getY()), 0.1f, 100.0f);
  camera.transform().setPosition({0.0f,0.5f,0.0f});

  const float sensitivity = 0.2f;
  const float speed = 10.0f;

  camera.transform().lookAt(camera.transform().getPosition() + Vector3f::Forward);
  Quaternion quat({45.0,45.0,45.0});
  quat.print();

  while (app.running()) {
    app.clear();
    app.poll();

    camera.update();
    transform.update();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }
    if (app.input().onKey(KeyCode::S)) {
      camera.transform().translate(camera.transform().forward() * -speed * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::W)) {
      camera.transform().translate(camera.transform().forward() *  speed * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::A)) {
      camera.transform().translate(camera.transform().right() * -speed * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::D)) {
      camera.transform().translate(camera.transform().right() *  speed * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::LEFT_SHIFT)) {
      camera.transform().translate(Vector3f(0.0f,-speed,0.0f) * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::SPACE)) {
      camera.transform().translate(Vector3f(0.0f, speed,0.0f) * app.deltaTime());
    }
    if (app.input().onMouseButton(MouseButton::RIGHT) && app.input().onMouseMove()) {
      Vector2f delta = app.input().getMouseDelta() * sensitivity;
      Vector3f rotation = camera.transform().getRotation() + Vector3f(delta.getY(), delta.getX(), 0.0f);
      if (rotation.getX() > 89.0f) rotation.setX(89.0f);
      else if (rotation.getX() < -89.0f) rotation.setX(-89.0f);
      rotation.setZ(0.0f);
      camera.transform().setRotation(rotation);
      // app.input().getMouseDelta().print();
    }

    // transform.rotate(Vector3f(30.0f * app.deltaTime(), 0.0f, 0.0f));
    // transform.rotate(Vector3f(0.0f, 30.0f * app.deltaTime(), 0.0f));
    // transform.rotate(Vector3f(0.0f, 0.0f, 30.0f * app.deltaTime()));

    flatShader.activate();
    tex.bind(0);
    flatShader.setUniformVec3f(uColor, color);
    flatShader.setUniform1i(uTexture, 0);
    flatShader.setUniformMat4(uModelMatrix, transform.matrix());
    flatShader.setUniformMat4(uCameraMatrix, camera.matrix());
    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    app.render();
  }

  app.clean();

  return 0;
}
