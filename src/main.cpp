#include "application.hpp"
#include "graphics/objects/ebo.hpp"
#include "graphics/objects/vao.hpp"
#include "graphics/objects/vbo.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "types/vector2i.hpp"
#include <GL/glew.h>
#include <iostream>

struct Vertex {
  float position[3];
  float uv[2];
};

int main() {
  Application app;

  app.init("My Application", 800, 600, false);

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

  while (app.running()) {
    app.poll();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    flatShader.activate();
    tex.bind(0);
    flatShader.setUniform3f(uColor, color);
    flatShader.setUniform1i(uTexture, 0);
    VAO::Bind(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    app.render();
  }

  app.clean();

  return 0;
}
