#ifndef JKR_TYPES_VECTOR_2_FLOAT_HPP
#define JKR_TYPES_VECTOR_2_FLOAT_HPP

class Vector3f;

class Vector2f {
  float data[2];
public:
  Vector2f();
  Vector2f(float x, float y);
  Vector2f(const Vector2f& other);
  
  // Accessors
  float getX() const;
  float getY() const;
  const float* ptr() const;

  // Mutators
  void set(float x, float y);
  void setX(float value);
  void setY(float value);
  void normalize();

  // Calculations
  double magnitude() const;
  float sqrMagnitude() const;
  Vector2f normalized() const;

  // Debuggig
  void print() const;

  // Operators
  Vector2f& operator=(const Vector2f& other);
  Vector2f& operator+=(const Vector2f& other);
  Vector2f& operator-=(const Vector2f& other);
  Vector2f operator+(const Vector2f& other) const;
  Vector2f operator-(const Vector2f& other) const;
  Vector2f operator-() const;
  Vector2f operator*(float scalar) const;
  Vector2f operator/(float scalar) const;
  bool operator==(const Vector2f& other) const;
  bool operator!=(const Vector2f& other) const;

  // Static Instances
  static const Vector2f Zero;
  static const Vector2f One;
  static const Vector2f Up;
  static const Vector2f Down;
  static const Vector2f Left;
  static const Vector2f Right;

  operator Vector3f() const;
};

#endif
