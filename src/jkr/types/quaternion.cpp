#include "quaternion.hpp"
#include "fmt/core.h"
#include "jkr/util/math.hpp"

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
Quaternion::Quaternion(const Quaternion& quat) : w(quat.w), x(quat.x), y(quat.y), z(quat.z) {}

Quaternion Quaternion::operator =(const Quaternion& other) {
  w = other.w;
  x = other.x;
  y = other.y;
  z = other.z;
  return *this;
}

Quaternion Quaternion::operator *(const Quaternion& other) const {
  return Quaternion(
    w * other.w - x * other.x - y * other.y - z * other.z,
    w * other.x + x * other.w + y * other.z - z * other.y,
    w * other.y - x * other.z + y * other.w + z * other.x,
    w * other.z + x * other.y - y * other.x + z * other.w
  );
}

Matrix4 Quaternion::matrix() const {
  float x2 = 2 * x * x;
  float y2 = 2 * y * y;
  float z2 = 2 * z * z;

  float wx = 2 * w * x;
  float wy = 2 * w * y;
  float wz = 2 * w * z;

  float xy = 2 * x * y;
  float xz = 2 * x * z;
  float yz = 2 * y * z;

  return Matrix4(
    1 - y2 - z2, xy - wz, xz + wy, 0.0f,
    xy + wz, 1 - x2 - z2, yz - wx, 0.0f,
    xz - wy, yz + wx, 1 - x2 - y2, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

float Quaternion::magnitude() const { 
  return sqrt(w * w + x * x + y * y + z * z);
}

float Quaternion::sqrMagnitude() const { 
  return w * w + x * x + y * y + z * z;
}

Quaternion Quaternion::normalized() const {
  float magnitude = sqrt(w * w + x * x + y * y + z * z);
  return Quaternion(
    w / magnitude,
    x / magnitude,
    y / magnitude,
    z / magnitude
  );
}

void Quaternion::normalize() {
  float magnitude = sqrt(w * w + x * x + y * y + z * z);
  w /= magnitude;
  x /= magnitude;
  y /= magnitude;
  z /= magnitude;
}

void Quaternion::rotate(const Quaternion& rotation) {
  *this = rotation * (*this);
}

void Quaternion::rotate(const Vector3f& degrees) {
  rotate(fromEuler(degrees));
}

void Quaternion::print() const {
  fmt::println("Quaternion: (w:{:f}, x:{:f}, y:{:f}, z:{:f})",w,x,y,z);
}

Quaternion Quaternion::fromEuler(const Vector3f& degrees, EulerOrder order) {
  float rx = radians(degrees.getX()) * 0.5f;
  float ry = radians(degrees.getY()) * 0.5f;
  float rz = -radians(degrees.getZ()) * 0.5f;
  Quaternion X(cos(rx), sin(rx), 0.0f, 0.0f);
  Quaternion Y(cos(ry), 0.0f, sin(ry), 0.0f);
  Quaternion Z(cos(rz), 0.0f, 0.0f, sin(rz));
  switch (order) {
    case EulerOrder::XYZ: return X * Y * Z;
    case EulerOrder::XZY: return X * Z * Y;
    case EulerOrder::YXZ: return Y * X * Z;
    case EulerOrder::YZX: return Y * Z * X;
    case EulerOrder::ZXY: return Z * X * Y;
    case EulerOrder::ZYX: return Z * Y * X;
  }
}

const Quaternion Quaternion::Identity = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
