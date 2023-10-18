#ifndef JKR_GRAPHICS_SHADER_PROGRAM_HPP
#define JKR_GRAPHICS_SHADER_PROGRAM_HPP

#include "jkr/graphics/texture.hpp"
#include "jkr/types/matrix4.hpp"
#include "jkr/types/vector3f.hpp"
#include "jkr/types/color3f.hpp"

class Shader {
  unsigned int shaderID;

public:
  Shader(const char* vertexFile, const char* fragmentFile);
  ~Shader();

  void activate();
  
  int getUniform(const char* name);
  void setUniformMat4(int uniform, const Matrix4& mat4);
  void setUniformVec3f(int uniform, const Vector3f* vec3, int count);
  void setUniformVec3f(int uniform, const Vector3f& vec3);
  void setUniformVec3f(int uniform, const Color3f& vec3);
  void setUniform1i(int uniform, int unit);
};

#endif
