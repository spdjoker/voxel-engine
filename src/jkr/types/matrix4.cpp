#include "matrix4.hpp"
#include "vector3f.hpp"
#include "jkr/util/math.hpp"
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

float Matrix4::operator[](int i) const {
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
    data[ 3]*mat4.data[12] + data[ 7]*mat4.data[13] + data[11]*mat4.data[14] + data[15]*mat4.data[15]
  });
}

Vector3f Matrix4::operator*(const Vector3f& t) const {
  return Vector3f(
    data[0] * t.data[0] + data[4] * t.data[1] + data[ 8] * t.data[2] + data[12],
    data[1] * t.data[0] + data[5] * t.data[1] + data[ 9] * t.data[2] + data[13],
    data[2] * t.data[0] + data[6] * t.data[1] + data[10] * t.data[2] + data[14]
  );
}

void Matrix4::scale(const Vector3f& s) {
  data[ 0] *= s.data[0];
  data[ 1] *= s.data[0];
  data[ 2] *= s.data[0];
  data[ 3] *= s.data[0];
  data[ 4] *= s.data[1];
  data[ 5] *= s.data[1];
  data[ 6] *= s.data[1];
  data[ 7] *= s.data[1];
  data[ 8] *= s.data[2];
  data[ 9] *= s.data[2];
  data[10] *= s.data[2];
  data[11] *= s.data[2];
}

void Matrix4::scaleX(float sx) {
  data[ 0] *= sx;
  data[ 1] *= sx;
  data[ 2] *= sx;
  data[ 3] *= sx;
}

void Matrix4::scaleY(float sy) {
  data[ 4] *= sy;
  data[ 5] *= sy;
  data[ 6] *= sy;
  data[ 7] *= sy;
}

void Matrix4::scaleZ(float sz) {
  data[ 8] *= sz;
  data[ 9] *= sz;
  data[10] *= sz;
  data[11] *= sz;
}

void Matrix4::translate(const Vector3f& t) {
  data[12] += data[0]*t.data[0] + data[4]*t.data[1] + data[ 8]*t.data[2];
  data[13] += data[1]*t.data[0] + data[5]*t.data[1] + data[ 9]*t.data[2];
  data[14] += data[2]*t.data[0] + data[6]*t.data[1] + data[10]*t.data[2];
  data[15] += data[3]*t.data[0] + data[7]*t.data[1] + data[11]*t.data[2];
}

void Matrix4::translateX(float tx) {
  data[12] += data[0]*tx;
  data[13] += data[1]*tx;
  data[14] += data[2]*tx;
  data[15] += data[3]*tx;
}

void Matrix4::translateY(float ty) {
  data[12] += data[4]*ty;
  data[13] += data[5]*ty;
  data[14] += data[6]*ty;
  data[15] += data[7]*ty;
}

void Matrix4::translateZ(float tz) {
  data[12] += data[ 8]*tz;
  data[13] += data[ 9]*tz;
  data[14] += data[10]*tz;
  data[15] += data[11]*tz;
}

void Matrix4::rotate(const Vector3f& right, const Vector3f& up, const Vector3f& forward) {
  float tmp1 = data[0];
  float tmp2 = data[4];
  data[ 0] = tmp1 * right.data[0] + tmp2 * up.data[0] + data[ 8] * forward.data[0];
  data[ 4] = tmp1 * right.data[1] + tmp2 * up.data[1] + data[ 8] * forward.data[1];
  data[ 8] = tmp1 * right.data[2] + tmp2 * up.data[2] + data[ 8] * forward.data[2];
  tmp1 = data[1];
  tmp2 = data[5];
  data[ 1] = tmp1 * right.data[0] + tmp2 * up.data[0] + data[ 9] * forward.data[0];
  data[ 5] = tmp1 * right.data[1] + tmp2 * up.data[1] + data[ 9] * forward.data[1];
  data[ 9] = tmp1 * right.data[2] + tmp2 * up.data[2] + data[ 9] * forward.data[2];
  tmp1 = data[2];
  tmp2 = data[6];
  data[ 2] = tmp1 * right.data[0] + tmp2 * up.data[0] + data[10] * forward.data[0];
  data[ 6] = tmp1 * right.data[1] + tmp2 * up.data[1] + data[10] * forward.data[1];
  data[10] = tmp1 * right.data[2] + tmp2 * up.data[2] + data[10] * forward.data[2];
  tmp1 = data[3];
  tmp2 = data[7];
  data[ 3] = tmp1 * right.data[0] + tmp2 * up.data[0] + data[11] * forward.data[0];
  data[ 7] = tmp1 * right.data[1] + tmp2 * up.data[1] + data[11] * forward.data[1];
  data[11] = tmp1 * right.data[2] + tmp2 * up.data[2] + data[11] * forward.data[2];
}

void Matrix4::rotateX(float degrees) {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  float tmp = data[ 8];
  data[ 8] = cosd*tmp - sind*data[4];
  data[ 4] = sind*tmp + cosd*data[4];
  tmp = data[ 9];
  data[ 9] = cosd*tmp - sind*data[5];
  data[ 5] = sind*tmp + cosd*data[5];
  tmp = data[10];
  data[10] = cosd*tmp - sind*data[6];
  data[ 6] = sind*tmp + cosd*data[6];
  tmp = data[11];
  data[11] = cosd*tmp - sind*data[7];
  data[ 7] = sind*tmp + cosd*data[7];
}

void Matrix4::rotateY(float degrees) {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  float tmp = data[0];
  data[ 0] = cosd*tmp - sind*data[ 8];
  data[ 8] = sind*tmp + cosd*data[ 8];
  tmp = data[1];
  data[ 1] = cosd*tmp - sind*data[ 9];
  data[ 9] = sind*tmp + cosd*data[ 9];
  tmp = data[2];
  data[ 2] = cosd*tmp - sind*data[10];
  data[10] = sind*tmp + cosd*data[10];
  tmp = data[3];
  data[ 3] = cosd*tmp - sind*data[11];
  data[11] = sind*tmp + cosd*data[11];
}

void Matrix4::rotateZ(float degrees) {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  float tmp = data[4];
  data[4] = cosd*tmp - sind*data[0];
  data[0] = sind*tmp + cosd*data[0];
  tmp = data[5];
  data[5] = cosd*tmp - sind*data[1];
  data[1] = sind*tmp + cosd*data[1];
  tmp = data[6];
  data[6] = cosd*tmp - sind*data[2];
  data[2] = sind*tmp + cosd*data[2];
  tmp = data[7];
  data[7] = cosd*tmp - sind*data[3];
  data[3] = sind*tmp + cosd*data[3];
}

Matrix4 Matrix4::scaled(const Vector3f& s) const {
  return Matrix4(
    data[ 0] * s.data[0], data[ 4] * s.data[1], data[ 8] * s.data[2], data[12],
    data[ 1] * s.data[0], data[ 5] * s.data[1], data[ 9] * s.data[2], data[13],
    data[ 2] * s.data[0], data[ 6] * s.data[1], data[10] * s.data[2], data[14],
    data[ 3] * s.data[0], data[ 7] * s.data[1], data[11] * s.data[2], data[15]
  );
}

Matrix4 Matrix4::scaledX(float sx) const {
  return Matrix4(
    data[ 0] * sx, data[ 4], data[ 8], data[12],
    data[ 1] * sx, data[ 5], data[ 9], data[13],
    data[ 2] * sx, data[ 6], data[10], data[14],
    data[ 3] * sx, data[ 7], data[11], data[15]
  );
}

Matrix4 Matrix4::scaledY(float sy) const {
  return Matrix4(
    data[ 0], data[ 4] * sy, data[ 8], data[12],
    data[ 1], data[ 5] * sy, data[ 9], data[13],
    data[ 2], data[ 6] * sy, data[10], data[14],
    data[ 3], data[ 7] * sy, data[11], data[15]
  );
}

Matrix4 Matrix4::scaledZ(float sz) const {
  return Matrix4(
    data[ 0], data[ 4], data[ 8] * sz, data[12],
    data[ 1], data[ 5], data[ 9] * sz, data[13],
    data[ 2], data[ 6], data[10] * sz, data[14],
    data[ 3], data[ 7], data[11] * sz, data[15]
  );
}

Matrix4 Matrix4::translated(const Vector3f& t) const {
  return Matrix4(
    data[ 0], data[ 4], data[ 8], data[12] + data[0] * t.data[0] + data[4] * t.data[1] + data[ 8] * t.data[2],
    data[ 1], data[ 5], data[ 9], data[13] + data[1] * t.data[0] + data[5] * t.data[1] + data[ 9] * t.data[2],
    data[ 2], data[ 6], data[10], data[14] + data[2] * t.data[0] + data[6] * t.data[1] + data[10] * t.data[2],
    data[ 3], data[ 7], data[11], data[15] + data[3] * t.data[0] + data[7] * t.data[1] + data[11] * t.data[2]
  );
}

Matrix4 Matrix4::translatedX(float tx) const {
  return Matrix4(
    data[ 0], data[ 4], data[ 8], data[12] + data[0] * tx,
    data[ 1], data[ 5], data[ 9], data[13] + data[1] * tx,
    data[ 2], data[ 6], data[10], data[14] + data[2] * tx,
    data[ 3], data[ 7], data[11], data[15] + data[3] * tx
  );
}

Matrix4 Matrix4::translatedY(float ty) const {
  return Matrix4(
    data[ 0], data[ 4], data[ 8], data[12] + data[4] * ty,
    data[ 1], data[ 5], data[ 9], data[13] + data[5] * ty,
    data[ 2], data[ 6], data[10], data[14] + data[6] * ty,
    data[ 3], data[ 7], data[11], data[15] + data[7] * ty
  );
}

Matrix4 Matrix4::translatedZ(float tz) const {
  return Matrix4(
    data[ 0], data[ 4], data[ 8], data[12] + data[ 8] * tz,
    data[ 1], data[ 5], data[ 9], data[13] + data[ 9] * tz,
    data[ 2], data[ 6], data[10], data[14] + data[10] * tz,
    data[ 3], data[ 7], data[11], data[15] + data[11] * tz
  );
}

Matrix4 Matrix4::rotatedX(float degrees) const {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  return Matrix4(
    data[0], sind * data[ 8] + cosd * data[4], cosd * data[ 8] - sind * data[4], data[12],
    data[1], sind * data[ 9] + cosd * data[5], cosd * data[ 9] - sind * data[5], data[13], 
    data[2], sind * data[10] + cosd * data[6], cosd * data[10] - sind * data[6], data[14],
    data[3], sind * data[11] + cosd * data[7], cosd * data[11] - sind * data[7], data[15]
  );
}

Matrix4 Matrix4::rotatedY(float degrees) const {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  return Matrix4(
    cosd * data[0] - sind * data[ 8], data[4], sind * data[0] + cosd * data[ 8], data[12],
    cosd * data[1] - sind * data[ 9], data[5], sind * data[1] + cosd * data[ 9], data[13],
    cosd * data[2] - sind * data[10], data[6], sind * data[2] + cosd * data[10], data[14],
    cosd * data[3] - sind * data[11], data[7], sind * data[3] + cosd * data[11], data[15]
  );
}

Matrix4 Matrix4::rotatedZ(float degrees) const {
  degrees = radians(degrees);
  float sind = sinf(degrees);
  float cosd = cosf(degrees);
  return Matrix4(
    sind * data[4] + cosd * data[0], cosd * data[4] - sind * data[0], data[ 8], data[12],
    sind * data[5] + cosd * data[1], cosd * data[5] - sind * data[1], data[ 9], data[13],
    sind * data[6] + cosd * data[2], cosd * data[6] - sind * data[2], data[10], data[14],
    sind * data[7] + cosd * data[3], cosd * data[7] - sind * data[3], data[11], data[15]
  );
}

Vector3f Matrix4::rowVector0() const {
  return Vector3f(data[0], data[4], data[8]);
}

Vector3f Matrix4::rowVector1() const {
  return Vector3f(data[1], data[5], data[9]);
}
Vector3f Matrix4::rowVector2() const {
  return Vector3f(data[2], data[6], data[10]);
}
Vector3f Matrix4::rowVector3() const {
  return Vector3f(data[3], data[7], data[11]);
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
