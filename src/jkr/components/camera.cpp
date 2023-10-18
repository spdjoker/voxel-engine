#include "camera.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

constexpr char MODIFIED_POSITION = 1;
constexpr char MODIFIED_ROTATION = 2;
constexpr char MODIFIED_PROJECTION_MATRIX = 4;

float radians(float degrees) {
  return degrees * M_PI / 180.0f;
}

Camera::Camera() : 
  projectionMatrix(), rotationMatrix(), viewMatrix(), cameraMatrix(), 
  recalculate(0), position(), orientation() {}

void Camera::perspective(float FOV, float aspect, float near, float far) {
  float tanHalfFOV = std::tan(radians(FOV) / 2.0f) ;
  projectionMatrix = {
    1.0f / (aspect * tanHalfFOV), 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f / tanHalfFOV, 0.0f, 0.0f,
    0.0f, 0.0f, -(far + near)/(far - near), -2 * far * near / (far - near),
    0.0f, 0.0f, -1.0f, 0.0f
  };

  recalculate |= MODIFIED_PROJECTION_MATRIX;
}

void Camera::update() {
  if (recalculate) {
    if (recalculate & MODIFIED_ROTATION) {
      recalculateRotationMatrix();
      recalculateViewMatrix();
    } else if (recalculate & MODIFIED_POSITION) {
      recalculateViewMatrix();
    }
    cameraMatrix = viewMatrix;
    recalculate = 0;
  }
}

void Camera::recalculateRotationMatrix() {
  float x = orientation.getX();
  float y = orientation.getY();
  float z = orientation.getZ();
  float x2 = x*x;
  float y2 = y*y;
  float z2 = z*z;
  float w = sqrt(1 - x2 - y2 - z2);
  float wx = w*x;
  float wy = w*y;
  float wz = w*z;
  float xy = x*y;
  float xz = x*z;
  float yz = y*z;

  rotationMatrix = {
    1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
    2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
    2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 - y2), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}

void Camera::recalculateViewMatrix() {
  Matrix4 translationMatrix({
    1.0f, 0.0f, 0.0f, -position.getX(),
    0.0f, 1.0f, 0.0f, -position.getY(),
    0.0f, 0.0f, 1.0f, position.getZ(),
    0.0f, 0.0f, 0.0f, 1.0f
  });
  viewMatrix = translationMatrix * rotationMatrix;
}

void Camera::move(const Vector3f& displacement) {
  position += displacement;
  recalculate |= MODIFIED_POSITION;
}

void Camera::rotate(const Vector3f& degrees) {
  float x = orientation.getX() + radians(degrees.getX());
  float y = orientation.getY() + radians(degrees.getY());
  float z = orientation.getZ() + radians(degrees.getZ());

  while (y >= 1.0f) {
    y -= 2.0f;
  }
  while (y <= -1.0f) {
    y += 2.0f;
  }

  orientation.set(x,y,z);

  orientation.print();
  recalculate |= MODIFIED_ROTATION;
}

const Matrix4& Camera::matrix() const {
  return cameraMatrix;
}
const Matrix4& Camera::pmatrix() const {
  return projectionMatrix;
}
