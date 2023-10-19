#include "transform.hpp"
#include "fmt/core.h"
#include "jkr/util/math.hpp"

constexpr unsigned char FLAG_MODIFIED_POSITION = 1;
constexpr unsigned char FLAG_MODIFIED_ROTATION = 2;
constexpr unsigned char FLAG_MODIFIED_SCALE = 4;
constexpr unsigned char FLAG_MODIFIED_PIVOT = 8;

Transform::Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& scale, const Vector3f& pivot) : 
  mat4_model(), mat4_rotation(), vec3_position(pos), vec3_rotation(rot), vec3_scale(scale), vec3_pivot(pivot),
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
    mat4_model.rotate(
      mat4_rotation.rowVector0(),  // Right Vector
      mat4_rotation.rowVector1(),  // Up Vector
      mat4_rotation.rowVector2()   // Forward Vector
    );
    mat4_model.scale(vec3_scale);
    mat4_model.translate({-vec3_pivot.getX(), -vec3_pivot.getY(), vec3_pivot.getZ()});

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

  mat4_rotation = Matrix4::Identity;
  mat4_rotation.rotateZ(vec3_rotation.getZ());
  mat4_rotation.rotateY(vec3_rotation.getY());
  mat4_rotation.rotateX(vec3_rotation.getX());

  m_events.setSignalFlags(FLAG_MODIFIED_ROTATION);
}

void Transform::lookAt(const Vector3f& target, const Vector3f& worldUp) {
  Vector3f tmp1 = (target - vec3_position).normalized();
  mat4_rotation[ 2] = tmp1.getX();
  mat4_rotation[ 6] = tmp1.getY();
  mat4_rotation[10] = tmp1.getZ();
  vec3_rotation.setX(degrees(std::asin(-tmp1.getY())));
  vec3_rotation.setY(degrees(std::atan2(tmp1.getX(), tmp1.getZ())));
  Vector3f tmp2 = worldUp.cross(tmp1).normalized(); // Right
  mat4_rotation[ 0] = tmp2.getX();
  mat4_rotation[ 4] = tmp2.getY();
  mat4_rotation[ 8] = tmp2.getZ();
  vec3_rotation.setZ(degrees(std::atan2(-tmp2.getY(), tmp2.getX())));
  tmp1 = tmp1.cross(tmp2); // Up
  mat4_rotation[ 1] = tmp1.getX();
  mat4_rotation[ 5] = tmp1.getY();
  mat4_rotation[ 9] = tmp1.getZ();

  m_events.setSignalFlags(FLAG_MODIFIED_ROTATION);
}

void Transform::setPosition(const Vector3f& position) {
  vec3_position = position;
  m_events.setSignalFlags(FLAG_MODIFIED_POSITION);
}

void Transform::setRotation(const Vector3f& rotation) {
  vec3_rotation = rotation;
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
  return mat4_rotation.rowVector0();
}

const Vector3f Transform::up() const {
  return mat4_rotation.rowVector1();
}

const Vector3f Transform::forward() const {
  return mat4_rotation.rowVector2();
}

const Matrix4& Transform::matrix() const {
  return mat4_model;
}

const Matrix4& Transform::rotationMatrix() const {
  return mat4_rotation;
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
