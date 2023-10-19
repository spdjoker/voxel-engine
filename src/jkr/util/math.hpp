#define _USE_MATH_DEFINES
#include <cmath>

constexpr float radians(float degrees) {
  return degrees * M_PI / 180.0f;
}

constexpr float degrees(float radians) {
  return radians * 180.0f / M_PI;
}
