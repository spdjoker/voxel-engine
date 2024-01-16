#include "shader.hpp"
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
            const char *fragmentFile)
: vertexFile(vertexFile), fragmentFile(fragmentFile) {
  // Read the files and store their contents
  std::string vertexCode = GetFileContents(vertexFile);
  std::string fragmentCode = GetFileContents(fragmentFile);

  // Converts the shader files into usable character strings
  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  // Create the vertex shader and store the reference
  shader_vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader_vert, 1, &vertexSource, NULL);
  glCompileShader(shader_vert);
  CompileErrors(shader_vert, "VERTEX");

  // Create the fragment shader and store the reference
  shader_frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader_frag, 1, &fragmentSource, NULL);
  glCompileShader(shader_frag);
  CompileErrors(shader_frag, "FRAGMENT");

  // Create the shader program and attach the shaders
  program = glCreateProgram();
  glAttachShader(program, shader_vert);
  glAttachShader(program, shader_frag);
  glLinkProgram(program);
  CompileErrors(program, "PROGRAM");

  // Delete the shaders
  glDeleteShader(shader_vert);
  glDeleteShader(shader_frag);
}

Shader::~Shader() {
  glDeleteShader(program);
}

void Shader::reload() {
  // Read the files and store their contents
  std::string vertexCode = GetFileContents(vertexFile);
  std::string fragmentCode = GetFileContents(fragmentFile);

  // Converts the shader files into usable character strings
  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();


  // Create the vertex shader and store the reference
  glDetachShader(program, shader_vert);
  shader_vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader_vert, 1, &vertexSource, NULL);
  glCompileShader(shader_vert);
  CompileErrors(shader_vert, "VERTEX");

  // Create the fragment shader and store the reference
  glDetachShader(program, shader_frag);
  shader_frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader_frag, 1, &fragmentSource, NULL);
  glCompileShader(shader_frag);
  CompileErrors(shader_frag, "FRAGMENT");

  glAttachShader(program, shader_vert);
  glAttachShader(program, shader_frag);
  glLinkProgram(program);
  CompileErrors(program, "PROGRAM");

  // Delete the shaders
  glDeleteShader(shader_vert);
  glDeleteShader(shader_frag);
}

void Shader::activate() { glUseProgram(program); }

int Shader::getUniform(const char *uniform) {
  return glGetUniformLocation(program, uniform);
}

void Shader::setUniformMat4(int uniform, const mat4& mat4) {
  glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::setUniformVec3f(int uniform, const vec3* vec3, int count) {
  glUniform3fv(uniform, count, glm::value_ptr(*vec3));
}

void Shader::setUniformVec3f(int uniform, const vec3& vec3) {
  glUniform3fv(uniform, 1, glm::value_ptr(vec3));
}

void Shader::setUniform1i(int uniform, int unit) {
  glUniform1i(uniform, unit);
}
