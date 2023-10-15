#ifndef JKR_GRAPHICS_SHADER_PROGRAM_HPP
#define JKR_GRAPHICS_SHADER_PROGRAM_HPP

#include "graphics/texture.hpp"
#include "types/vector3f.hpp"

class Shader {
  unsigned int shaderID;

public:
  Shader(const char* vertexFile, const char* fragmentFile);
  ~Shader();

  void activate();
  
  int getUniform(const char* name);
  void setUniform3fv(int uniform, Vector3f* vec3, int count);
  void setUniform3f(int uniform, const Vector3f& vec3);
  void setUniform1i(int uniform, int unit);
};

#endif
