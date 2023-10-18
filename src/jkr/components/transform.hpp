#ifndef JKR_COMPONENTS_TRANSFORM_HPP
#define JKR_COMPONENTS_TRANSFORM_HPP

#include "jkr/types/matrix4.hpp"
#include "jkr/types/vector3f.hpp"

class Transform {
  Matrix4 modelMatrix;
  Vector3f m_position;
  Vector3f m_rotation;
  Vector3f m_scale;

  bool recalculate;

public:
  Transform(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale);

  void move(const Vector3f& displacement);

  void update();

  const Matrix4& matrix() const;
};

#endif
