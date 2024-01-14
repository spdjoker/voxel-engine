#ifndef JKR_COMPONENTS_CAMERA_HPP
#define JKR_COMPONENTS_CAMERA_HPP

#include "transform.hpp"
#include "jkr/types/common.hpp"

class Camera {
  mat4 mat4_projection;
  mat4 mat4_view;
  mat4 mat4_camera;

  Transform m_transform;
  flag8 flags;

public:
  Camera(const Transform& transform);
  
  void perspective(float fovy, float aspect, float near, float far);
  void update();

  Transform& transform();

  const mat4& matrix() const;
  const mat4& matrix_view() const;
  const mat4& matrix_projection() const;
};

#endif
