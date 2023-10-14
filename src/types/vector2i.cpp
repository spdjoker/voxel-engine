#include "vector2i.hpp"
#include <cmath>

Vector2i::Vector2i() : data{0,0} {}
Vector2i::Vector2i(int x, int y) : data{x,y} {}
Vector2i::Vector2i(const Vector2i& other) : data{other.data[0],other.data[1]} {}

int Vector2i::getX() const {
  return data[0];
}

void Vector2i::setX(int value) {
  data[0] = value;
}

int Vector2i::getY() const {
  return data[1];
}

void Vector2i::setY(int value) {
  data[1] = value;
}

void Vector2i::set(int x, int y) {
  data[0] = x;
  data[1] = y;
}

double Vector2i::magnitude() const {
  return sqrt(data[0] * data[0] + data[1] * data[1]);
}

int Vector2i::sqrMagnitude() const {
  return data[0] * data[0] + data[1] * data[1];
}

Vector2i& Vector2i::operator=(const Vector2i& other) {
  data[0] = other.data[0];
  data[1] = other.data[1];
  return *this;
}

bool Vector2i::operator==(const Vector2i& other) const {
  return data[0] == other.data[0] && data[1] == other.data[1];
}

bool Vector2i::operator!=(const Vector2i& other) const {
  return data[0] != other.data[0] || data[1] != other.data[1];
}

Vector2i Vector2i::Zero   = Vector2i( 0, 0);
Vector2i Vector2i::One    = Vector2i( 1, 1);
Vector2i Vector2i::Up     = Vector2i( 0, 1);
Vector2i Vector2i::Down   = Vector2i( 0,-1);
Vector2i Vector2i::Left   = Vector2i(-1, 0);
Vector2i Vector2i::Right  = Vector2i( 1, 0);
