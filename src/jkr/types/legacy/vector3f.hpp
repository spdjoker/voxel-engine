#ifndef JKR_TYPES_VECTOR_3_FLOAT_HPP
#define JKR_TYPES_VECTOR_3_FLOAT_HPP

class Matrix4;

class Vector3f {
  float data[3];
public:
  Vector3f();
  Vector3f(float x, float y, float z);
  Vector3f(const Vector3f& other);
  
  // Accessors
  float getX() const;
  float getY() const;
  float getZ() const;
  const float* ptr() const;

  // Mutators
  void set(float x, float y, float z);
  void setX(float value);
  void setY(float value);
  void setZ(float value);
  void normalize();

  // Calculations
  double magnitude() const;
  float sqrMagnitude() const;
  Vector3f normalized() const;
  Vector3f cross(const Vector3f& other) const;

  // Debuggig
  void print() const;

  // Operators
  Vector3f& operator=(const Vector3f& other);
  Vector3f& operator+=(const Vector3f& other);
  Vector3f& operator-=(const Vector3f& other);
  Vector3f operator+(const Vector3f& other) const;
  Vector3f operator-(const Vector3f& other) const;
  Vector3f operator-() const;
  Vector3f operator*(float scalar) const;
  Vector3f operator/(float scalar) const;
  bool operator==(const Vector3f& other) const;
  bool operator!=(const Vector3f& other) const;

  // Static Instances
  static const Vector3f Zero;
  static const Vector3f One;
  static const Vector3f Up;
  static const Vector3f Down;
  static const Vector3f Left;
  static const Vector3f Right;
  static const Vector3f Forward;
  static const Vector3f Back;
  
  // Friends
  friend class Matrix4;
};

#endif
