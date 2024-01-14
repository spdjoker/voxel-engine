#include "vector2f.hpp"
#include "fmt/core.h"
#include <cmath>

#include "../vector3f.hpp"

Vector2f::Vector2f() : data{0.0f,0.0f} {}
Vector2f::Vector2f(float x, float y) : data{x,y} {}
Vector2f::Vector2f(const Vector2f& other) : 
  data{other.data[0],other.data[1]} {}

float Vector2f::getX() const { return data[0]; }

void Vector2f::setX(float value) { data[0] = value; }

float Vector2f::getY() const { return data[1]; }

void Vector2f::setY(float value) { data[1] = value; }

void Vector2f::set(float x, float y) {
  data[0] = x;
  data[1] = y;
}

void Vector2f::normalize() {
  float mag = sqrt(data[0]*data[0] + data[1]*data[1]);
  data[0] /= mag;
  data[1] /= mag;
}

double Vector2f::magnitude() const {
  return sqrt(data[0] * data[0] + data[1] * data[1]);
}

float Vector2f::sqrMagnitude() const {
  return data[0] * data[0] + data[1] * data[1];
}

Vector2f Vector2f::normalized() const {
  float mag = sqrt(data[0]*data[0] + data[1]*data[1]);
  return Vector2f(data[0] / mag, data[1] / mag);
}

const float* Vector2f::ptr() const {
  return data;
}

Vector2f& Vector2f::operator=(const Vector2f& other) {
  data[0] = other.data[0];
  data[1] = other.data[1];
  return *this;
}

Vector2f& Vector2f::operator+=(const Vector2f& other) {
  data[0] += other.data[0];
  data[1] += other.data[1];
  return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other) {
  data[0] -= other.data[0];
  data[1] -= other.data[1];
  return *this;
}

Vector2f Vector2f::operator+(const Vector2f& other) const {
  return Vector2f(data[0]+other.data[0], data[1]+other.data[1]);
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
  return Vector2f(data[0]-other.data[0], data[1]-other.data[1]);
}

Vector2f Vector2f::operator-() const {
  return Vector2f(-data[0], -data[1]);
}

Vector2f Vector2f::operator*(float scalar) const {
  return Vector2f(data[0]*scalar, data[1]*scalar);
}

Vector2f Vector2f::operator/(float scalar) const {
  float inverse = 1.0f / scalar;
  return Vector2f(data[0]*inverse, data[1]*inverse);
}

bool Vector2f::operator==(const Vector2f& other) const {
  return data[0] == other.data[0] && data[1] == other.data[1];
}

bool Vector2f::operator!=(const Vector2f& other) const {
  return data[0] != other.data[0] || data[1] != other.data[1];
}

void Vector2f::print() const {
  fmt::println("Vector2f: ({:f},{:f})",data[0],data[1]);
}

Vector2f::operator Vector3f() const { return Vector3f(data[0],data[1],0.0f); }

const Vector2f Vector2f::Zero     = Vector2f( 0.0f, 0.0f);
const Vector2f Vector2f::One      = Vector2f( 1.0f, 1.0f);
const Vector2f Vector2f::Up       = Vector2f( 0.0f, 1.0f);
const Vector2f Vector2f::Down     = Vector2f( 0.0f,-1.0f);
const Vector2f Vector2f::Left     = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::Right    = Vector2f( 1.0f, 0.0f);
