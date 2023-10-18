#ifndef JKR_GRAPHICS_OBJECTS_VBO_HPP
#define JKR_GRAPHICS_OBJECTS_VBO_HPP

namespace VBO {

void Create(unsigned int &vboID, void* data, int sizeBytes, bool dynamic = false);
void Delete(unsigned int &vboID);
void Update(unsigned int vboID, void* data, int sizeBytes);
void Bind(unsigned int vboID);
void Unbind();

}

#endif
