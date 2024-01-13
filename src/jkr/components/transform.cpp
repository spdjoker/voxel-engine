#include "transform.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "jkr/types/common.hpp"
#include <fmt/core.h>

enum FLAGS {
  MODIFIED_POSITION = 1,
  MODIFIED_ROTATION = 2,
  MODIFIED_SCALE = 4,
  MODIFIED_PIVOT = 8
};

Transform::Transform(const vec3& pos, const vec3& rotation, const vec3& scale, const vec3& pivot) : 
  mat4_model(), quat_rotation(glm::radians(rotation)), vec3_position(pos), vec3_rotation(rotation), vec3_scale(scale), vec3_pivot(pivot),
  flags(MODIFIED_POSITION | MODIFIED_ROTATION | MODIFIED_SCALE | MODIFIED_PIVOT) {
  update();
}

Transform::Transform(const vec3& pos, const quat& rotation, const vec3& scale, const vec3& pivot) : 
  mat4_model(), quat_rotation(rotation), vec3_position(pos), vec3_rotation(glm::degrees(glm::eulerAngles(rotation))), vec3_scale(scale), vec3_pivot(pivot),
  flags(MODIFIED_POSITION | MODIFIED_ROTATION | MODIFIED_SCALE | MODIFIED_PIVOT) {
  update();
}

void Transform::update() {
  if (flags.hasSignalFlags()) {
    mat4_model = glm::translate(MAT4_IDENTITY, vec3_position + vec3_pivot) * glm::mat4_cast(quat_rotation);
    mat4_model = glm::scale(mat4_model, vec3_scale);
    mat4_model = glm::translate(mat4_model, -vec3_pivot);

    flags.processSignalFlags();
  } else if (flags.hasEventFlags()) {
    flags.clearEventFlags();
  }
}

void Transform::translate(const vec3& translation) {
  vec3_position += translation;
  flags.setSignalFlags(MODIFIED_POSITION);
}

void Transform::rotate(const vec3& rot_degrees) {
  vec3_rotation += rot_degrees;
  quat_rotation = quat(glm::radians(vec3_rotation));
  flags.setSignalFlags(MODIFIED_ROTATION);
}

void Transform::setPosition(const vec3& position) {
  vec3_position = position;
  flags.setSignalFlags(MODIFIED_POSITION);
}

void Transform::setRotation(const vec3& rot_degrees) {
  vec3_rotation = rot_degrees;
  quat_rotation = quat(glm::radians(vec3_rotation));
  flags.setSignalFlags(MODIFIED_ROTATION);
}

void Transform::setRotation(const quat& rotation) {
  quat_rotation = rotation;
  vec3_rotation = glm::degrees(glm::eulerAngles(quat_rotation));
  flags.setSignalFlags(MODIFIED_ROTATION);
}

void Transform::setScale(const vec3& scale) {
  vec3_scale = scale;
  flags.setSignalFlags(MODIFIED_SCALE);
}

void Transform::setPivot(const vec3& pivot) {
  vec3_pivot = pivot;
  flags.setSignalFlags(MODIFIED_PIVOT);
}

void Transform::print() const {
  fmt::print("Transform: {{\n\tpos: ({},{},{})\n\trot: ({},{},{},{})\n\tsca: ({},{},{})\n\tpiv: ({},{},{})\n}}\n", 
               vec3_position.x, vec3_position.y, vec3_position.z, 
               quat_rotation.w, quat_rotation.x, quat_rotation.y, quat_rotation.z,
               vec3_scale.x, vec3_scale.y, vec3_scale.z, 
               vec3_pivot.x, vec3_pivot.y, vec3_pivot.z 
             );
}

const vec3& Transform::getScale() const {
  return vec3_scale;
}

const vec3& Transform::getPosition() const {
  return vec3_position;
}

const vec3& Transform::getRotation() const {
  return vec3_rotation;
}

const vec3& Transform::getPivot() const {
  return vec3_pivot;
}

const vec3 Transform::right() const {
  return quat_rotation * VEC3_RIGHT;
}

const vec3 Transform::up() const {
  return quat_rotation * VEC3_UP;
}

const vec3 Transform::forward() const {
  return quat_rotation * VEC3_FORWARD;
}

const mat4& Transform::matrix() const {
  return mat4_model;
}

const quat& Transform::quaternion() const {
  return quat_rotation;
}

bool Transform::onPositionChange() const {
  return flags.getEventFlags(MODIFIED_POSITION);
}

bool Transform::onRotationChange() const {
  return flags.getEventFlags(MODIFIED_ROTATION);
}

bool Transform::onScaleChange() const {
  return flags.getEventFlags(MODIFIED_SCALE);
}

bool Transform::onPivotChange() const {
  return flags.getEventFlags(MODIFIED_PIVOT);
}

bool Transform::onChange() const {
  return flags.hasEventFlags();
}
