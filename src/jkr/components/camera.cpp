#include "camera.hpp"
#include "fmt/core.h"
#include "jkr/util/math.hpp"

constexpr unsigned char FLAG_MODIFIED_PROJECTION_MATRIX = 1;
constexpr unsigned char FLAG_MODIFIED_VIEW_MATRIX = 2;
constexpr unsigned char FLAG_MODIFIED_ROTATION_MATRIX = 4;

Camera::Camera() : 
  mat4_projection(), mat4_view(), mat4_camera(), m_transform(), 
  m_events(FLAG_MODIFIED_PROJECTION_MATRIX | FLAG_MODIFIED_VIEW_MATRIX | FLAG_MODIFIED_ROTATION_MATRIX) {}

void Camera::perspective(float FOV, float aspect, float near, float far) {
  float tanHalfFOV = std::tan(radians(FOV) / 2.0f) ;
  mat4_projection = {
    1.0f / (aspect * tanHalfFOV), 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f / tanHalfFOV, 0.0f, 0.0f,
    0.0f, 0.0f, -(far + near)/(far - near), -2 * far * near / (far - near),
    0.0f, 0.0f, -1.0f, 0.0f
  };
  m_events.setSignalFlags(FLAG_MODIFIED_PROJECTION_MATRIX);
}

void Camera::update() {
  m_transform.update();

  if (m_events.hasSignalFlags() || m_transform.onChange()) {
    // Invert the forward vector of the rotation matrix.
    mat4_view = Matrix4::Identity.translated(-m_transform.getPivot());
    mat4_view.rotate(m_transform.right(), m_transform.up(), -m_transform.forward());
    mat4_view.scale(m_transform.getScale());
    mat4_view.translate(-m_transform.getPosition() - m_transform.getPivot());
    
    mat4_camera = mat4_projection * mat4_view;
    m_events.processSignalFlags();
  } else if (m_events.hasEventFlags()) {
    m_events.clearEventFlags();
  }
}

Transform& Camera::transform() {
  return m_transform;
}

const Matrix4& Camera::projectionMatrix() const {
  return mat4_projection;
}

const Matrix4& Camera::matrix() const {
  return mat4_camera;
}

const Matrix4& Camera::viewMatrix() const {
  return mat4_view;
}
