#include "jkr/components/camera.hpp"
#include "jkr/engine/application.hpp"
#include "jkr/graphics/objects/ebo.hpp"
#include "jkr/graphics/objects/vao.hpp"
#include "jkr/graphics/objects/vbo.hpp"
#include "jkr/graphics/shader.hpp"
#include "jkr/graphics/texture.hpp"
#include "jkr/types/matrix4.hpp"
#include "jkr/types/vector2i.hpp"
#include "jkr/types/vector3f.hpp"
#include <GL/glew.h>
#include <iostream>

struct Vertex {
  float position[3];
  float color[3];
  float uv[2];
};

int main() {
  Application app;

  app.init("My Application", 800, 600);
  // app.init("My Fullscreen Application");

  Shader flatShader("resources/shaders/vertex-vert.glsl", "resources/shaders/vertex-frag.glsl");
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  Vertex vertices[] = {
    {{-0.5f, -0.5f,  0.0f}, {1.0f,0.0f,0.0f}, {0.0f, 0.0f}},    // Vertex 0
    {{-0.5f,  0.5f,  0.0f}, {0.0f,1.0f,0.0f}, {0.0f, 1.0f}},    // Vertex 1
    {{ 0.5f,  0.5f,  0.0f}, {0.0f,0.0f,1.0f}, {1.0f, 1.0f}},    // Vertex 2
    {{ 0.5f, -0.5f,  0.0f}, {1.0f,0.0f,1.0f}, {1.0f, 0.0f}}    // Vertex 3
  };

  unsigned int indices[] = {
    0, 1, 2, 0, 2, 3
  };

  Vector3f color(1.0f, 1.0f, 1.0f);
  
  VAO::Create(vao);
  VAO::Bind(vao);
  VBO::Create(vbo, vertices, sizeof(vertices));
  EBO::Create(ebo, indices, sizeof(indices));
  VAO::LinkAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  VAO::LinkAttribute(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)offsetof(Vertex,color));
  VAO::LinkAttribute(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)offsetof(Vertex, uv));

  Texture tex("resources/images/gridbox.jpg");
  
  flatShader.activate();
  // int uColor = flatShader.getUniform("uColor");
  int uTexture = flatShader.getUniform("uTex");
  int uModelMatrix = flatShader.getUniform("uModelMatrix");
  int uCameraMatrix = flatShader.getUniform("uCameraMatrix");
  int uProjMatrix = flatShader.getUniform("uProjMatrix");

  Matrix4 modelMatrix({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  });

  // Set up the camera
  Camera camera;
  camera.perspective(60.0f, ((float)app.windowSize().getX())/((float)app.windowSize().getY()), 0.1f, 100.0f);
  camera.move(Vector3f(0.0f,0.0f,-2.0f));

  Matrix4 mat(
     0.0f,  1.0f,  2.0f,  3.0f,
     4.0f,  5.0f,  6.0f,  7.0f,
     8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f
  );
  mat.print();

  float degrees = 20.0f;

  while (app.running()) {
    app.clear();
    app.poll();
    camera.update();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }
    if (app.input().onKey(KeyCode::S)) {
      camera.move(Vector3f::Back);
    }
    if (app.input().onKey(KeyCode::W)) {
      camera.move(Vector3f::Forward);
    }
    if (app.input().onKey(KeyCode::A)) {
      camera.move(Vector3f::Left);
    }
    if (app.input().onKey(KeyCode::D)) {
      camera.move(Vector3f::Right);
    }
    if (app.input().onKey(KeyCode::E)) {
      camera.rotate(Vector3f(0.0f, degrees, 0.0f) * app.deltaTime());
    }
    if (app.input().onKey(KeyCode::Q)) {
      camera.rotate(Vector3f(0.0f, -degrees, 0.0f) * app.deltaTime());
    }

    flatShader.activate();
    tex.bind(0);
    // flatShader.setUniformVec3f(uColor, color);
    flatShader.setUniform1i(uTexture, 0);
    flatShader.setUniformMat4(uModelMatrix, modelMatrix);
    flatShader.setUniformMat4(uCameraMatrix, camera.matrix());
    flatShader.setUniformMat4(uProjMatrix, camera.pmatrix());
    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    modelMatrix.rotateY(30.0f * app.deltaTime());

    app.render();
  }

  app.clean();

  return 0;
}
