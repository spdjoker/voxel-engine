#include "vbo.hpp"
#include <GL/glew.h>

namespace VBO {

void Create(unsigned int &vboID, void *data, int sizeBytes, bool dynamic) {
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeBytes, data,
               dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void Delete(unsigned int &vboID) {
  glDeleteBuffers(1, &vboID);
  vboID = 0;
}

void Update(unsigned int vboID, void* data, int sizeBytes) {
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeBytes, data);
}

void Bind(unsigned int vboID) {
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace VBO
