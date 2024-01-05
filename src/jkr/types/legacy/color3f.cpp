#include "color3f.hpp"
#include <cmath>

Color3f::Color3f() : data{1.0f,1.0f,1.0f} {}
Color3f::Color3f(float r, float g, float b) : data{r,g,b} {}
Color3f::Color3f(const Color3f& other) : 
  data{other.data[0],other.data[1],other.data[2]} {}

float Color3f::getR() const {
  return data[0];
}

void Color3f::setR(float value) {
  data[0] = value;
}

float Color3f::getG() const {
  return data[1];
}

void Color3f::setG(float value) {
  data[1] = value;
}

float Color3f::getB() const {
  return data[2];
}

void Color3f::setB(float value) {
  data[2] = value;
}

void Color3f::set(float r, float g, float b) {
  data[0] = r;
  data[1] = g;
  data[2] = b;
}

const float* Color3f::ptr() const {
  return data;
}

Color3f& Color3f::operator=(const Color3f& other) {
  data[0] = other.data[0];
  data[1] = other.data[1];
  data[2] = other.data[2];
  return *this;
}

bool Color3f::operator==(const Color3f& other) const {
  return data[0] == other.data[0] && data[1] == other.data[1] && data[2] == other.data[2];
}

bool Color3f::operator!=(const Color3f& other) const {
  return data[0] != other.data[0] || data[1] != other.data[1] || data[2] != other.data[2];
}

const Color3f Color3f::White    = Color3f( 1.0f, 1.0f, 1.0f);
const Color3f Color3f::Red      = Color3f( 1.0f, 0.0f, 0.0f);
const Color3f Color3f::Green    = Color3f( 0.0f, 1.0f, 0.0f);
const Color3f Color3f::Blue     = Color3f( 0.0f, 0.0f, 1.0f);
const Color3f Color3f::Cyan     = Color3f( 0.0f, 1.0f, 1.0f);
const Color3f Color3f::Magenta  = Color3f( 1.0f, 0.0f, 1.0f);
const Color3f Color3f::Yellow   = Color3f( 1.0f, 1.0f, 0.0f);
const Color3f Color3f::Black    = Color3f( 0.0f, 0.0f, 0.0f);
