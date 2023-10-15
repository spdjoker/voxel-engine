#ifndef JKR_GRAPHICS_TEXTURE_HPP
#define JKR_GRAPHICS_TEXTURE_HPP

struct TexData;

class Texture {
  TexData* data;

public:
  Texture(const char* imageFile);

  void bind(unsigned int unit);

  unsigned int getId() const;
  bool valid() const;
  static void clean();
};

#endif // !JKR_GRAPHICS_TEXTURE_HPP
