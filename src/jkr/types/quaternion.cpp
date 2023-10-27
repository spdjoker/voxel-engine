#include "quaternion.hpp"
#include "fmt/core.h"
#include "jkr/util/math.hpp"

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
Quaternion::Quaternion(const Vector3f& eulerAngles) {
  z = radians(eulerAngles.getZ()) / 2.0f;
  y = radians(eulerAngles.getY()) / 2.0f;
  float tmp1 = cos(z);  // Roll w
  float tmp2 = sin(z);  // Roll z
  float tmp3 = cos(y);  // Yaw  w
           z = sin(y);  // Yaw  z

  w =  tmp1 * tmp3;
  x = -tmp2 * z;
  y =  tmp1 * z;
  z =  tmp2 * tmp3;
  tmp1 = radians(eulerAngles.getX()) / 2.0f;
  tmp2 = cos(tmp1);  // Pitch w
  tmp3 = sin(tmp1);  // Pitch x
  tmp1 = w;
  w = tmp1 * tmp2 - x * tmp3;
  x = tmp1 * tmp3 + x * tmp2;
  tmp1 = y;
  y =  tmp1 * tmp2 + z * tmp3;
  z = -tmp1 * tmp3 + z * tmp2;
}

Quaternion Quaternion::operator *(const Quaternion& other) const {
  return Quaternion(
    w * other.w - x * other.x - y * other.y - z * other.z,
    w * other.x + x * other.w + y * other.z - z * other.y,
    w * other.y - x * other.z + y * other.w + z * other.x,
    w * other.z + x * other.y - y * other.x + z * other.w
  );
}

void Quaternion::print() const {
  fmt::println("Quaternion: (w:{:f}, x:{:f}, y:{:f}, z:{:f})",w,x,y,z);
}
