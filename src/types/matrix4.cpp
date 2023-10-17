#include "matrix4.hpp"
#include "vector3f.hpp"
#include <fmt/core.h>
#include <stdexcept>

Matrix4::Matrix4() :
  data{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  } {}

Matrix4::Matrix4(
  float m00, float m01, float m02, float m03,
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23,
  float m30, float m31, float m32, float m33
) : data{
    m00, m10, m20, m30,
    m01, m11, m21, m31,
    m02, m12, m22, m32,
    m03, m13, m23, m33
} {}

Matrix4::Matrix4(const Matrix4& mat4) :
  data{
    mat4.data[ 0],mat4.data[ 1],mat4.data[ 2],mat4.data[ 3],
    mat4.data[ 4],mat4.data[ 5],mat4.data[ 6],mat4.data[ 7],
    mat4.data[ 8],mat4.data[ 9],mat4.data[10],mat4.data[11],
    mat4.data[12],mat4.data[13],mat4.data[14],mat4.data[15],
  }{}

float& Matrix4::at(int row, int col) {
  if (row < 0 || col < 0 || row >= SIZE_ROW || col >= SIZE_COL) {
    throw std::out_of_range("Matrix element indices are out of bounds.");
  }
  return data[row + col * SIZE_COL];
}

const float* Matrix4::ptr() const {
  return data;
}

float& Matrix4::operator[](int i) {
  return data[i];
}

Matrix4& Matrix4::operator=(const Matrix4& mat4) {
  data[ 0] = mat4.data[ 0];
  data[ 1] = mat4.data[ 1];
  data[ 2] = mat4.data[ 2];
  data[ 3] = mat4.data[ 3];
  data[ 4] = mat4.data[ 4];
  data[ 5] = mat4.data[ 5];
  data[ 6] = mat4.data[ 6];
  data[ 7] = mat4.data[ 7];
  data[ 8] = mat4.data[ 8];
  data[ 9] = mat4.data[ 9];
  data[10] = mat4.data[10];
  data[11] = mat4.data[11];
  data[12] = mat4.data[12];
  data[13] = mat4.data[13];
  data[14] = mat4.data[14];
  data[15] = mat4.data[15];
  return *this;
}

Matrix4& Matrix4::operator=(const float mat4[SIZE]) {
  data[ 0] = mat4[ 0];
  data[ 1] = mat4[ 4];
  data[ 2] = mat4[ 8];
  data[ 3] = mat4[12];
  data[ 4] = mat4[ 1];
  data[ 5] = mat4[ 5];
  data[ 6] = mat4[ 9];
  data[ 7] = mat4[13];
  data[ 8] = mat4[ 2];
  data[ 9] = mat4[ 6];
  data[10] = mat4[10];
  data[11] = mat4[14];
  data[12] = mat4[ 3];
  data[13] = mat4[ 7];
  data[14] = mat4[11];
  data[15] = mat4[15];
  return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat4) const {
  return Matrix4({
    data[ 0]*mat4.data[ 0] + data[ 4]*mat4.data[ 1] + data[ 8]*mat4.data[ 2] + data[12]*mat4.data[ 3],
    data[ 0]*mat4.data[ 4] + data[ 4]*mat4.data[ 5] + data[ 8]*mat4.data[ 6] + data[12]*mat4.data[ 7],
    data[ 0]*mat4.data[ 8] + data[ 4]*mat4.data[ 9] + data[ 8]*mat4.data[10] + data[12]*mat4.data[11],
    data[ 0]*mat4.data[12] + data[ 4]*mat4.data[13] + data[ 8]*mat4.data[14] + data[12]*mat4.data[15],

    data[ 1]*mat4.data[ 0] + data[ 5]*mat4.data[ 1] + data[ 9]*mat4.data[ 2] + data[13]*mat4.data[ 3],
    data[ 1]*mat4.data[ 4] + data[ 5]*mat4.data[ 5] + data[ 9]*mat4.data[ 6] + data[13]*mat4.data[ 7],
    data[ 1]*mat4.data[ 8] + data[ 5]*mat4.data[ 9] + data[ 9]*mat4.data[10] + data[13]*mat4.data[11],
    data[ 1]*mat4.data[12] + data[ 5]*mat4.data[13] + data[ 9]*mat4.data[14] + data[13]*mat4.data[15],

    data[ 2]*mat4.data[ 0] + data[ 6]*mat4.data[ 1] + data[10]*mat4.data[ 2] + data[14]*mat4.data[ 3],
    data[ 2]*mat4.data[ 4] + data[ 6]*mat4.data[ 5] + data[10]*mat4.data[ 6] + data[14]*mat4.data[ 7],
    data[ 2]*mat4.data[ 8] + data[ 6]*mat4.data[ 9] + data[10]*mat4.data[10] + data[14]*mat4.data[11],
    data[ 2]*mat4.data[12] + data[ 6]*mat4.data[13] + data[10]*mat4.data[14] + data[14]*mat4.data[15],

    data[ 3]*mat4.data[ 0] + data[ 7]*mat4.data[ 1] + data[11]*mat4.data[ 2] + data[15]*mat4.data[ 3],
    data[ 3]*mat4.data[ 4] + data[ 7]*mat4.data[ 5] + data[11]*mat4.data[ 6] + data[15]*mat4.data[ 7],
    data[ 3]*mat4.data[ 8] + data[ 7]*mat4.data[ 9] + data[11]*mat4.data[10] + data[15]*mat4.data[11],
    data[ 3]*mat4.data[12] + data[ 7]*mat4.data[13] + data[11]*mat4.data[14] + data[15]*mat4.data[15],
  });
}

Vector3f Matrix4::operator*(const Vector3f& vec3) const {
  return Vector3f(
    data[0] * vec3.data[0] + data[4] * vec3.data[1] + data[ 8] * vec3.data[2] + data[12],
    data[1] * vec3.data[0] + data[5] * vec3.data[1] + data[ 9] * vec3.data[2] + data[13],
    data[2] * vec3.data[0] + data[6] * vec3.data[1] + data[10] * vec3.data[2] + data[14]
  );
}

void Matrix4::print() const {
  fmt::println("Matrix4:"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
             ,data[ 0],data[ 4],data[ 8],data[12]
             ,data[ 1],data[ 5],data[ 9],data[13]
             ,data[ 2],data[ 6],data[10],data[14]
             ,data[ 3],data[ 7],data[11],data[15]
             );
}

void Matrix4::printArray() const {
  fmt::println("Matrix4:"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
              "\n[ {:12.2f} {:12.2f} {:12.2f} {:12.2f} ]"
             ,data[ 0],data[ 1],data[ 2],data[ 3]
             ,data[ 4],data[ 5],data[ 6],data[ 7]
             ,data[ 8],data[ 9],data[10],data[11]
             ,data[12],data[13],data[14],data[15]
             );
}

const Matrix4 Matrix4::Identity = Matrix4();
