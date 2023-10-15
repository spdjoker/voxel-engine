#ifndef JKR_GRAPHICS_OBJECTS_VAO_HPP
#define JKR_GRAPHICS_OBJECTS_VAO_HPP

namespace VAO {

void Create(unsigned int &vaoID);
void Delete(unsigned int &vaoID);
void Bind(unsigned int &vaoID);
void Unbind();

void LinkAttribute(unsigned int vbo, unsigned int layout,
                   unsigned int numComponents, unsigned int type, int stride,
                   void *offset);
void LinkAttribute(unsigned int vbo, unsigned int layout,
                   unsigned int numComponents, unsigned int type,
                   bool normalize, int stride, void *offset);

} // namespace VAO

#endif
