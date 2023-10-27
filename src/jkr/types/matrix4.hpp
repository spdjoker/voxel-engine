#ifndef JKR_TYPES_MATRIX_4_BY_4_HPP
#define JKR_TYPES_MATRIX_4_BY_4_HPP


class Vector3f;

class Matrix4 {
  constexpr static int SIZE_COL = 4;
  constexpr static int SIZE_ROW = 4;
  constexpr static int SIZE = SIZE_COL * SIZE_ROW;
  float data[SIZE];
  
public:
  Matrix4();
  Matrix4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
  );
  Matrix4(const Matrix4& mat4);

  float& at(int row, int col);
  const float* ptr() const;
  
  float& operator[](int i);
  float operator[](int i) const;
  Matrix4& operator=(const Matrix4& mat4);
  Matrix4& operator=(const float mat4[SIZE]);
  Matrix4 operator*(const Matrix4& mat4) const;
  Vector3f operator*(const Vector3f& vec3) const;
  
  // Matrix Transformations
  void scale(const Vector3f& s);
  void scaleX(float sx);
  void scaleY(float sy);
  void scaleZ(float sz);

  void translate(const Vector3f& t);
  void translateX(float tx);
  void translateY(float ty);
  void translateZ(float tz);
  
  void rotate(const Vector3f& right, const Vector3f& up, const Vector3f& forward);
  void rotateX(float degrees);
  void rotateY(float degrees);
  void rotateZ(float degrees);

  // Returned Transformations
  Matrix4 scaled(const Vector3f& s) const;
  Matrix4 scaledX(float sx) const;
  Matrix4 scaledY(float sy) const;
  Matrix4 scaledZ(float sz) const;

  Matrix4 translated(const Vector3f& t) const;
  Matrix4 translatedX(float tx) const;
  Matrix4 translatedY(float ty) const;
  Matrix4 translatedZ(float tz) const;
  
  Matrix4 rotated(const Vector3f& right, const Vector3f& up, const Vector3f& forward) const;
  Matrix4 rotatedX(float degrees) const;
  Matrix4 rotatedY(float degrees) const;
  Matrix4 rotatedZ(float degrees) const;

  Vector3f rowVector0() const;
  Vector3f rowVector1() const;
  Vector3f rowVector2() const;
  Vector3f rowVector3() const;

  // Helper Methods
  void print() const;
  void printArray() const;

  static const Matrix4 Identity;
};

#endif
