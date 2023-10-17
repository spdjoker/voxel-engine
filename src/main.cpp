#include "components/camera.hpp"
#include "engine/application.hpp"
#include "graphics/objects/ebo.hpp"
#include "graphics/objects/vao.hpp"
#include "graphics/objects/vbo.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "types/matrix4.hpp"
#include "types/vector2i.hpp"
#include "types/vector3f.hpp"
#include <GL/glew.h>
#include <iostream>

struct Vertex {
  float position[3];
  float uv[2];
};

int main() {
  Application app;

  app.init("My Application", 800, 600);
  // app.init("My Fullscreen Application");

  Shader flatShader("resources/shaders/sprite-vert.glsl", "resources/shaders/sprite-frag.glsl");
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  Vertex vertices[] = {
    {{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f}},    // Vertex 0
    {{-0.5f,  0.5f,  0.0f}, {0.0f, 1.0f}},    // Vertex 1
    {{ 0.5f,  0.5f,  0.0f}, {1.0f, 1.0f}},    // Vertex 2
    {{ 0.5f, -0.5f,  0.0f}, {1.0f, 0.0f}}    // Vertex 3
  };

  unsigned int indices[] = {
    0, 1, 2, 0, 2, 3
  };

  Vector3f color(1.0f, 1.0f, 1.0f);
  
  VAO::Create(vao);
  VAO::Bind(vao);
  VBO::Create(vbo, vertices, sizeof(vertices));
  EBO::Create(ebo, indices, sizeof(indices));
  VAO::LinkAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  VAO::LinkAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)offsetof(Vertex, uv));

  Texture tex("resources/images/gridbox.jpg");
  
  flatShader.activate();
  int uColor = flatShader.getUniform("uColor");
  int uTexture = flatShader.getUniform("uTex");
  int uModelMatrix = flatShader.getUniform("uModelMatrix");
  int uCameraMatrix = flatShader.getUniform("uCameraMatrix");

  Matrix4 mat4({
    1.0f, 0.0f, 0.0f,  0.0f,
    0.0f, 1.0f, 0.0f,  0.0f,
    0.0f, 0.0f, 1.0f, -1.0f,
    0.0f, 0.0f, 0.0f,  1.0f,
  });

  float windowSizeX = app.windowSize().getX();
  float windowSizeY = app.windowSize().getY();

  Camera camera;
  camera.perspective(90.0f, windowSizeX/windowSizeY, 0.1f, 100.0f);
  camera.move(Vector3f(0.0f,0.0f,-2.0f));

  const Input& input = app.input();
  float degrees = 20.0f;

  while (app.running()) {
    app.clear();
    app.poll();
    camera.update();

    if (input.onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    if (input.onKey(KeyCode::S)) {
      camera.move(Vector3f::Back);
    }
    if (input.onKey(KeyCode::W)) {
      camera.move(Vector3f::Forward);
    }
    if (input.onKey(KeyCode::A)) {
      camera.move(Vector3f::Left);
    }
    if (input.onKey(KeyCode::D)) {
      camera.move(Vector3f::Right);
    }
    if (input.onKey(KeyCode::E)) {
      camera.rotate(Vector3f(0.0f, 0.0f, degrees) * app.deltaTime());
    }
    if (input.onKey(KeyCode::Q)) {
      camera.rotate(Vector3f(0.0f, 0.0f,-degrees) * app.deltaTime());
    }

    flatShader.activate();
    tex.bind(0);
    flatShader.setUniformVec3f(uColor, color);
    flatShader.setUniform1i(uTexture, 0);
    flatShader.setUniformMat4(uModelMatrix, mat4);
    flatShader.setUniformMat4(uCameraMatrix, camera.matrix());
    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    app.render();
  }

  app.clean();

  return 0;
}
