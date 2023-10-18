#ifndef JKR_TYPES_VECTOR_3_FLOAT_HPP
#define JKR_TYPES_VECTOR_3_FLOAT_HPP

class Matrix4;

class Vector3f {
  float data[3];
public:
  Vector3f();
  Vector3f(float x, float y, float z);
  Vector3f(const Vector3f& other);

  float getX() const;
  void setX(float value);

  float getY() const;
  void setY(float value);
  
  float getZ() const;
  void setZ(float value);

  void set(float x, float y, float z);

  void normalize();

  double magnitude() const;
  float sqrMagnitude() const;
  const float* ptr() const;
  
  Vector3f& operator=(const Vector3f& other);
  Vector3f& operator+=(const Vector3f& other);
  Vector3f& operator-=(const Vector3f& other);
  Vector3f operator+(const Vector3f& other) const;
  Vector3f operator-(const Vector3f& other) const;
  Vector3f operator*(float scalar) const;
  Vector3f operator/(float scalar) const;
  bool operator==(const Vector3f& other) const;
  bool operator!=(const Vector3f& other) const;


  void print() const;

  static Vector3f Zero;
  static Vector3f One;
  static Vector3f Up;
  static Vector3f Down;
  static Vector3f Left;
  static Vector3f Right;
  static Vector3f Forward;
  static Vector3f Back;

  friend class Matrix4;
};

#endif
