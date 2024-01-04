#include "transform.hpp"
#include "fmt/core.h"
#include "jkr/types/quaternion.hpp"
#include "jkr/types/vector3f.hpp"
#include "jkr/util/math.hpp"

constexpr unsigned char FLAG_MODIFIED_POSITION = 1;
constexpr unsigned char FLAG_MODIFIED_ROTATION = 2;
constexpr unsigned char FLAG_MODIFIED_SCALE = 4;
constexpr unsigned char FLAG_MODIFIED_PIVOT = 8;

Transform::Transform(const Vector3f& pos, const Quaternion& quaternion, const Vector3f& scale, const Vector3f& pivot) : 
  mat4_model(), quat_rotation(quaternion), vec3_position(pos), vec3_rotation(), vec3_scale(scale), vec3_pivot(pivot),
  m_events(FLAG_MODIFIED_POSITION | FLAG_MODIFIED_ROTATION | FLAG_MODIFIED_SCALE | FLAG_MODIFIED_PIVOT) {
  update();
}

void Transform::update() {
  if (m_events.hasSignalFlags()) {
    // Model Matrix
    mat4_model = Matrix4::Identity;
    mat4_model.translate({
         vec3_position.getX() + vec3_pivot.getX(),
         vec3_position.getY() + vec3_pivot.getY(),
         vec3_position.getZ() + vec3_pivot.getZ(),
    });
    // TODO: replace vectors with Matrix3
    mat4_model = mat4_model * quat_rotation.matrix();
    mat4_model.scale(vec3_scale);
    mat4_model.translate({-vec3_pivot.getX(), -vec3_pivot.getY(), -vec3_pivot.getZ()});

    m_events.processSignalFlags();
  } else if (m_events.hasEventFlags()) {
    m_events.clearEventFlags();
  }
}

void Transform::translate(const Vector3f& t) {
  vec3_position += t;
  m_events.setSignalFlags(FLAG_MODIFIED_POSITION);
}

void Transform::rotate(const Vector3f& r) {
  vec3_rotation += r;
  quat_rotation = Quaternion::fromEuler(vec3_rotation);
  m_events.setSignalFlags(FLAG_MODIFIED_ROTATION);
}

void Transform::setPosition(const Vector3f& position) {
  vec3_position = position;
  m_events.setSignalFlags(FLAG_MODIFIED_POSITION);
}

void Transform::setRotation(const Vector3f& rotation) {
  vec3_rotation = rotation;
  quat_rotation = Quaternion::fromEuler(vec3_rotation);
  m_events.setSignalFlags(FLAG_MODIFIED_ROTATION);
}

void Transform::setScale(const Vector3f& scale) {
  vec3_scale = scale;
  m_events.setSignalFlags(FLAG_MODIFIED_SCALE);
}

void Transform::setPivot(const Vector3f& pivot) {
  vec3_pivot = pivot;
  m_events.setSignalFlags(FLAG_MODIFIED_PIVOT);
}

void Transform::print() const {
  fmt::println("Transform:");
  vec3_position.print();
  vec3_rotation.print();
  vec3_scale.print();
  vec3_pivot.print();
  fmt::println("");
}

const Vector3f& Transform::getScale() const {
  return vec3_scale;
}

const Vector3f& Transform::getPosition() const {
  return vec3_position;
}

const Vector3f& Transform::getRotation() const {
  return vec3_rotation;
}

const Vector3f& Transform::getPivot() const {
  return vec3_pivot;
}

const Vector3f Transform::right() const {
  return quat_rotation.matrix().rowVector0();
}

const Vector3f Transform::up() const {
  return quat_rotation.matrix().rowVector1();
}

const Vector3f Transform::forward() const {
  return quat_rotation.matrix().rowVector2();
}

const Matrix4& Transform::matrix() const {
  return mat4_model;
}

const Quaternion& Transform::quaternion() const {
  return quat_rotation;
}

bool Transform::onPositionChange() const {
  return m_events.getEventFlags(FLAG_MODIFIED_POSITION);
}

bool Transform::onRotationChange() const {
  return m_events.getEventFlags(FLAG_MODIFIED_ROTATION);
}

bool Transform::onScaleChange() const {
  return m_events.getEventFlags(FLAG_MODIFIED_SCALE);
}

bool Transform::onPivotChange() const {
  return m_events.getEventFlags(FLAG_MODIFIED_PIVOT);
}

bool Transform::onChange() const {
  return m_events.hasEventFlags();
}
