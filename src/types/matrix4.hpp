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
  Matrix4& operator=(const Matrix4& mat4);
  Matrix4& operator=(const float mat4[SIZE]);
  Matrix4 operator*(const Matrix4& mat4) const;
  Vector3f operator*(const Vector3f& vec3) const;

  void print() const;
  void printArray() const;

  static const Matrix4 Identity;
};

#endif
