#include "vao.hpp"
#include "vbo.hpp"
#include <GL/glew.h>

namespace VAO {

void Create(unsigned int &vaoID) { glGenVertexArrays(1, &vaoID); }

void Delete(unsigned int &vaoID) {
  glDeleteVertexArrays(1, &vaoID);
  vaoID = 0;
}

void Bind(unsigned int &vaoID) { glBindVertexArray(vaoID); }

void Unbind() { glBindVertexArray(0); }

void LinkAttribute(unsigned int vbo, unsigned int layout,
                   unsigned int numComponents, unsigned int type, int stride,
                   void *offset) {
  VBO::Bind(vbo);
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO::Unbind();
}

void LinkAttribute(unsigned int vbo, unsigned int layout,
                   unsigned int numComponents, unsigned int type,
                   bool normalize, int stride, void *offset) {
  VBO::Bind(vbo);
  glVertexAttribPointer(layout, numComponents, type,
                        normalize ? GL_TRUE : GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO::Unbind();
}

} // namespace VAO
