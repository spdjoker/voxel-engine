#include "texture.hpp"
#include "jkr/util/stb_image.h"
#include <Gl/glew.h>
#include <gl/GL.h>
#include <iostream>
#include <unordered_map>
#include <vector>

struct TexData { unsigned int id; int width; int height; };

std::unordered_map<const char*, TexData> textures;

Texture::Texture(const char* imagePath) {
  auto pair = textures.insert({imagePath,TexData{}});
  data = &pair.first->second;
  
  // If the texture exists already, do not make another copy;
  if (!pair.second && data->id) {
    return;
  }
  
  glGenTextures(1, &data->id);
  glBindTexture(GL_TEXTURE_2D, data->id);

  // Set texture parameters for pixel art
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  int channels = 0;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* pixels = stbi_load(imagePath, &data->width, &data->height, &channels, 0);

  if (pixels) {
    GLenum format = GL_RED;

    if (channels == 4) {
      format = GL_RGBA;
    } else if (channels == 3) {
      format = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, data->width, data->height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    glDeleteTextures(1, &data->id);
    data->id = 0;
    data->width = 0;
    data->height = 0;
    std::cout << "Failed to load image " << imagePath << '\n';
  }

  stbi_image_free(pixels);
}

void Texture::bind(unsigned int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, data->id);
}

bool Texture::valid() const {
  return data->id != 0;
}

void Texture::clean() {
  for (auto& tex : textures) {
    if (tex.second.id) {
      glDeleteTextures(1, &tex.second.id);
      tex.second.id = 0;
      tex.second.width = 0;
      tex.second.height = 0;
    }
  }
}
