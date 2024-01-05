#ifndef JKR_GRAPHICS_SHADER_PROGRAM_HPP
#define JKR_GRAPHICS_SHADER_PROGRAM_HPP

#include "jkr/graphics/texture.hpp"
#include <jkr/types/common.hpp>

class Shader {
  unsigned int shaderID;

public:
  Shader(const char* vertexFile, const char* fragmentFile);
  ~Shader();

  void activate();
  
  int getUniform(const char* name);
  void setUniformMat4(int uniform, const mat4& mat4);
  void setUniformVec3f(int uniform, const vec3* vec3, int count);
  void setUniformVec3f(int uniform, const vec3& vec3);
  void setUniform1i(int uniform, int unit);
};

#endif
