#ifndef JKR_COMPONENTS_TRANSFORM_HPP
#define JKR_COMPONENTS_TRANSFORM_HPP

#include "jkr/types/common.hpp"

class Transform {
  mat4 mat4_model;
  quat quat_rotation;
  vec3 vec3_position;
  vec3 vec3_rotation;
  vec3 vec3_scale;
  vec3 vec3_pivot;
  flag8 flags;

public:
  Transform(
    const vec3& position = VEC3_ZERO,
    const vec3& rotation = VEC3_ZERO,
    const vec3& scale = VEC3_ONE,
    const vec3& pivot = VEC3_ZERO
  );
  Transform(
    const vec3& position,
    const quat& rotation,
    const vec3& scale = VEC3_ONE,
    const vec3& pivot = VEC3_ZERO
  );

  void update();

  void translate(const vec3& translation);
  void rotate(const vec3& rot_degrees);

  void setPosition(const vec3& position);
  void setRotation(const vec3& rot_degrees);
  void setRotation(const quat& rotation);
  void setScale(const vec3& scale);
  void setPivot(const vec3& pivot);

  void print() const;

  const vec3& getPosition() const;
  const vec3& getRotation() const;
  const vec3& getScale() const;
  const vec3& getPivot() const;
  const vec3 right() const;
  const vec3 up() const;
  const vec3 forward() const;

  const mat4& matrix() const;
  const quat& quaternion() const;

  bool onPositionChange() const;
  bool onRotationChange() const;
  bool onScaleChange() const;
  bool onPivotChange() const;
  bool onChange() const;
};

#endif
