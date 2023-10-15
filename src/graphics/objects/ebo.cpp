#include "ebo.hpp"
#include <GL/glew.h>

namespace EBO {

void Create(unsigned int &eboID, unsigned int *indices, int sizeBytes) {
  glGenBuffers(1, &eboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeBytes, indices, GL_STATIC_DRAW);
}

void Delete(unsigned int &eboID) { glDeleteBuffers(1, &eboID); }

void Bind(unsigned int eboID) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID); }

void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace EBO
