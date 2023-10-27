#ifndef JKR_TYPES_QUATERNION_HPP
#define JKR_TYPES_QUATERNION_HPP 

#include "vector3f.hpp"

class Quaternion {
  float w, x, y, z;

public:
  Quaternion();
  Quaternion(float w, float x, float y, float z);
  Quaternion(const Vector3f& eulerAngles);

  Quaternion operator *(const Quaternion& other) const;

  void print() const;
};

#endif
