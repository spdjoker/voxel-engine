#include "shader.hpp"
#include "types/matrix4.hpp"
#include "types/vector3f.hpp"
#include <GL/glew.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

void CompileErrors(unsigned int shader, const char *type) {
  GLint hasCompiled;
  char infoLog[1024];

  if (std::strcmp(type, "PROGRAM")) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_COMPILATION_ERROR for : " << type << '\n'
                << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_LINKING_ERROR for: " << type << '\n'
                << infoLog << std::endl;
    }
  }
}


std::string GetFileContents(const char *filename) {
  std::ifstream inputFile(filename, std::ios::binary);

  if (inputFile) {
    std::string contents;
    inputFile.seekg(0, std::ios::end);
    contents.resize(inputFile.tellg());

    inputFile.seekg(0, std::ios::beg);
    inputFile.read(&contents[0], contents.size());
    inputFile.close();

    return contents;
  }
  std::cout << "Failed to get file contents of shader: " << filename << '\n';
  throw(errno);
}

Shader::Shader(const char *vertexFile,
            const char *fragmentFile) {
  // Read the files and store their contents
  std::string vertexCode = GetFileContents(vertexFile);
  std::string fragmentCode = GetFileContents(fragmentFile);

  // Converts the shader files into usable character strings
  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  // Create the vertex shader and store the reference
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  CompileErrors(vertexShader, "VERTEX");

  // Create the fragment shader and store the reference
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  CompileErrors(fragmentShader, "FRAGMENT");

  // Create the shader program and attach the shaders
  shaderID = glCreateProgram();
  glAttachShader(shaderID, vertexShader);
  glAttachShader(shaderID, fragmentShader);
  glLinkProgram(shaderID);
  CompileErrors(shaderID, "PROGRAM");

  // Delete the shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  glDeleteShader(shaderID);
}

void Shader::activate() { glUseProgram(shaderID); }

int Shader::getUniform(const char *uniform) {
  return glGetUniformLocation(shaderID, uniform);
}

void Shader::setUniformMat4(int uniform, const Matrix4& mat4) {
  glUniformMatrix4fv(uniform, 1, GL_FALSE, mat4.ptr());
}

void Shader::setUniformVec3f(int uniform, const Vector3f* vec3, int count) {
  glUniform3fv(uniform, count, (float*)vec3);
}

void Shader::setUniformVec3f(int uniform, const Vector3f& vec3) {
  glUniform3fv(uniform, 1, vec3.ptr());
}

void Shader::setUniformVec3f(int uniform, const Color3f& color3) {
  glUniform3fv(uniform, 1, color3.ptr());
}

void Shader::setUniform1i(int uniform, int unit) {
  glUniform1i(uniform, unit);
}
