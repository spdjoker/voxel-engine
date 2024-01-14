#include "camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "jkr/types/common.hpp"
#include <fmt/core.h>

enum FLAGS {
  MODIFIED_PROJECTION = 1,
  MODIFIED_VIEW = 2
};

Camera::Camera(const Transform& transform) : 
  mat4_projection(MAT4_IDENTITY), mat4_view(MAT4_IDENTITY), mat4_camera(), 
  m_transform(transform), flags(MODIFIED_PROJECTION | MODIFIED_VIEW) {}

void Camera::perspective(float fovy, float aspect, float near, float far) {
  mat4_projection = glm::perspectiveLH(fovy, aspect, near, far);
  flags.setSignalFlags(MODIFIED_PROJECTION);
}

void Camera::update() {
  m_transform.update();

  if (flags.hasSignalFlags() || m_transform.onChange()) {
    // Invert the forward vector of the rotation matrix.
    mat4_view = glm::lookAtLH(m_transform.getPosition(), m_transform.getPosition() + m_transform.forward(), VEC3_UP);
    mat4_camera = mat4_projection * mat4_view;

    flags.processSignalFlags();
  } else if (flags.hasEventFlags()) {
    flags.clearEventFlags();
  }
}

Transform& Camera::transform() {
  return m_transform;
}

const mat4& Camera::matrix() const {
  return mat4_camera;
}

const mat4& Camera::matrix_projection() const {
  return mat4_projection;
}

const mat4& Camera::matrix_view() const {
  return mat4_view;
}
