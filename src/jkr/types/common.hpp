#ifndef JKR_TYPES_COMMON_HPP
#define JKR_TYPES_COMMON_HPP

#include "flag.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Sized Unsigned Integers
using glm::uint8;
using glm::uint16;
using glm::uint32;
using glm::uint64;

// Sized Integers
using glm::int8;
using glm::int16;
using glm::int32;
using glm::int64;

// Sized Event Flags
using flag8  = flags<uint8>;
using flag16 = flags<uint16>;
using flag32 = flags<uint32>;
using flag64 = flags<uint64>;

// Boolean Vectors
using glm::bvec2;
using glm::bvec3;
using glm::bvec4;
// Signed Int Vectors
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
// Unsigned Int Vectors
using glm::uvec2;
using glm::uvec3;
using glm::uvec4;
// Single-Precision Vectors
using glm::vec2;
using glm::vec3;
constexpr vec3 VEC3_ZERO    = vec3(0.0f);
constexpr vec3 VEC3_ONE     = vec3(1.0f);
constexpr vec3 VEC3_RIGHT   = vec3(1.0f, 0.0f, 0.0f);
constexpr vec3 VEC3_LEFT    = -VEC3_RIGHT;
constexpr vec3 VEC3_UP      = vec3(0.0f, 1.0f, 0.0f);
constexpr vec3 VEC3_DOWN    = -VEC3_UP;
constexpr vec3 VEC3_FORWARD = vec3(0.0f, 0.0f, 1.0f);
constexpr vec3 VEC3_BACK    = -VEC3_FORWARD;
using glm::vec4;
// Double-Precision Vectors
using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
// Quaternions
using glm::quat;
constexpr quat QUAT_IDENTITY = quat(1.0f,0.0f,0.0f,0.0f);
// Square Matrices
using glm::mat2;
constexpr mat2 MAT2_IDENTITY = mat2(1.0f);
using glm::mat3;
constexpr mat3 MAT3_IDENTITY = mat3(1.0f);
using glm::mat4;
constexpr mat4 MAT4_IDENTITY = mat4(1.0f);

#endif
