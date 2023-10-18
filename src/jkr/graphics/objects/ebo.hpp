#ifndef JKR_GRAPHICS_OBJECTS_EBO_HPP
#define JKR_GRAPHICS_OBJECTS_EBO_HPP

namespace EBO {
  
  void Create(unsigned int &eboID, unsigned int *indices, int sizeBytes);
  void Delete(unsigned int &eboID);
  void Bind(unsigned int eboID);
  void Unbind();

}

#endif
