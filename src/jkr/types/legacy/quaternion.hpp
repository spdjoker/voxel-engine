#ifndef JKR_TYPES_QUATERNION_HPP
#define JKR_TYPES_QUATERNION_HPP 

#include "jkr/types/matrix4.hpp"
#include "vector3f.hpp"

enum class EulerOrder {
  XYZ,
  XZY,
  YXZ,
  YZX,
  ZXY,
  ZYX
};

class Quaternion {
  float w, x, y, z;

public:
  Quaternion();
  Quaternion(float w, float x, float y, float z);
  Quaternion(const Quaternion& quat);

  Quaternion operator =(const Quaternion& other);
  Quaternion operator *(const Quaternion& other) const;

  Matrix4 matrix() const;
  float magnitude() const;
  float sqrMagnitude() const;
  Quaternion normalized() const;

  void normalize();
  void rotate(const Quaternion& rotation);
  void rotate(const Vector3f& degrees);

  void print() const;
  
  static Quaternion fromEuler(const Vector3f& degrees, EulerOrder order = EulerOrder::XYZ);

  static const Quaternion Identity;
};

#endif
