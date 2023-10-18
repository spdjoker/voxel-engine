#ifndef JKR_TYPES_COLOR_3_FLOAT_HPP
#define JKR_TYPES_COLOR_3_FLOAT_HPP

class Color3f {
  float data[3];
public:
  Color3f();
  Color3f(float r, float g, float b);
  Color3f(const Color3f& other);

  float getR() const;
  void setR(float value);

  float getG() const;
  void setG(float value);
  
  float getB() const;
  void setB(float value);

  void set(float r, float g, float b);

  double magnitude() const;
  float sqrMagnitude() const;
  const float* ptr() const;
  
  Color3f& operator=(const Color3f& other);
  bool operator==(const Color3f& other) const;
  bool operator!=(const Color3f& other) const;

  static const Color3f White;
  static const Color3f Red;
  static const Color3f Green;
  static const Color3f Blue;
  static const Color3f Cyan;
  static const Color3f Magenta;
  static const Color3f Yellow;
  static const Color3f Black;
};

#endif
