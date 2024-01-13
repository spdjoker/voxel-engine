#ifndef JKR_COMPONENTS_TRANSFORM_HPP
#define JKR_COMPONENTS_TRANSFORM_HPP

#include "jkr/types/matrix4.hpp"
#include "jkr/types/quaternion.hpp"
#include "jkr/types/vector3f.hpp"
#include "jkr/util/event_flags.hpp"

class Transform {
  Matrix4 mat4_model;
  Quaternion quat_rotation;
  Vector3f vec3_position;
  Vector3f vec3_rotation;
  Vector3f vec3_scale;
  Vector3f vec3_pivot;
  EventFlags1b m_events;

public:
  Transform(
    const Vector3f& position = Vector3f::Zero,
    const Quaternion& quaternion = Quaternion::Identity,
    const Vector3f& scale = Vector3f::One,
    const Vector3f& pivot = Vector3f::Zero
  );

  void update();

  void translate(const Vector3f& t);
  void rotate(const Vector3f& degrees);

  void setPosition(const Vector3f& position);
  void setRotation(const Vector3f& rotation);
  void setScale(const Vector3f& scale);
  void setPivot(const Vector3f& scale);

  void print() const;

  const Vector3f& getPosition() const;
  const Vector3f& getRotation() const;
  const Vector3f& getScale() const;
  const Vector3f& getPivot() const;
  const Vector3f right() const;
  const Vector3f up() const;
  const Vector3f forward() const;

  const Matrix4& matrix() const;
  const Quaternion& quaternion() const;

  bool onPositionChange() const;
  bool onRotationChange() const;
  bool onScaleChange() const;
  bool onPivotChange() const;
  bool onChange() const;
};

#endif
