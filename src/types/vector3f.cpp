#include "vector3f.hpp"
#include <cmath>

Vector3f::Vector3f() : data{0.0f,0.0f,0.0f} {}
Vector3f::Vector3f(float x, float y, float z) : data{x,y,z} {}
Vector3f::Vector3f(const Vector3f& other) : 
  data{other.data[0],other.data[1],other.data[2]} {}

float Vector3f::getX() const {
  return data[0];
}

void Vector3f::setX(float value) {
  data[0] = value;
}

float Vector3f::getY() const {
  return data[1];
}

void Vector3f::setY(float value) {
  data[1] = value;
}

float Vector3f::getZ() const {
  return data[2];
}

void Vector3f::setZ(float value) {
  data[2] = value;
}

void Vector3f::set(float x, float y, float z) {
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

double Vector3f::magnitude() const {
  return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
}

float Vector3f::sqrMagnitude() const {
  return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

const float* Vector3f::ptr() const {
  return data;
}

Vector3f& Vector3f::operator=(const Vector3f& other) {
  data[0] = other.data[0];
  data[1] = other.data[1];
  data[2] = other.data[2];
  return *this;
}

bool Vector3f::operator==(const Vector3f& other) const {
  return data[0] == other.data[0] && data[1] == other.data[1] && data[2] == other.data[2];
}

bool Vector3f::operator!=(const Vector3f& other) const {
  return data[0] != other.data[0] || data[1] != other.data[1] || data[2] != other.data[2];
}

Vector3f Vector3f::Zero     = Vector3f( 0.0f, 0.0f, 0.0f);
Vector3f Vector3f::One      = Vector3f( 1.0f, 1.0f, 1.0f);
Vector3f Vector3f::Up       = Vector3f( 0.0f, 1.0f, 0.0f);
Vector3f Vector3f::Down     = Vector3f( 0.0f,-1.0f, 0.0f);
Vector3f Vector3f::Left     = Vector3f(-1.0f, 0.0f, 0.0f);
Vector3f Vector3f::Right    = Vector3f( 1.0f, 0.0f, 0.0f);
Vector3f Vector3f::Forward  = Vector3f( 0.0f, 1.0f, 0.0f);
Vector3f Vector3f::Back     = Vector3f( 0.0f,-1.0f, 0.0f);
