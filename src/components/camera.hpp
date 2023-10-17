#ifndef JKR_COMPONENTS_CAMERA_HPP
#define JKR_COMPONENTS_CAMERA_HPP

#include "types/vector3f.hpp"
#include "types/matrix4.hpp"

class Camera {
public:
  enum class Projection {
    PERSPECTIVE,
    ORTHOGRAPHIC
  };

  Camera();
  
  // void orthographic(float left, float right, float bottom, float top, float near, float far);
  // void perspective(float left, float right, float bottom, float top, float near, float far);
  void perspective(float FOV, float aspect, float near, float far);
  void update();

  void move(const Vector3f& displacement);
  void rotate(const Vector3f& degrees);

  // void setPosition(const Vector3f& position);
  // void setRotation(const Vector3f& position);

  const Matrix4& matrix() const;

private:
  Matrix4 projectionMatrix;
  Matrix4 rotationMatrix;
  Matrix4 viewMatrix;
  Matrix4 cameraMatrix;
  char recalculate;

  Vector3f position;
  Vector3f orientation;

  void recalculateRotationMatrix();
  void recalculateViewMatrix();
};

#endif
