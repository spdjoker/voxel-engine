#include "transform.hpp"

Transform::Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& scale) : 
  modelMatrix(), m_position(), m_rotation(rot), m_scale(scale), recalculate(true) {}

void Transform::update() {
  
}
