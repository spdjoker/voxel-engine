#ifndef JKR_COMPONENTS_CAMERA_HPP
#define JKR_COMPONENTS_CAMERA_HPP

#include "jkr/components/transform.hpp"

class Camera {
  Matrix4 mat4_projection;
  Matrix4 mat4_view;
  Matrix4 mat4_camera;

  Transform m_transform;
  EventFlags1b m_events;

public:
  Camera();
  
  void perspective(float FOV, float aspect, float near, float far);
  void update();

  Transform& transform();

  const Matrix4& projectionMatrix() const;
  const Matrix4& viewMatrix() const;
  const Matrix4& matrix() const;
};

#endif
