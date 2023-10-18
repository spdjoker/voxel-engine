#include "tests.hpp"
#include "jkr/types/matrix4.hpp"
#include <fmt/core.h>

bool compare_result(const Matrix4& result, const Matrix4& answer) {
  for (int i = 0; i < 16; i++) {
    if (result[i] != answer[i]) {
      return false;
    }
  }
  return true;
}

void test_rotation(const Matrix4& matrix) {
  fmt::println("\nTesting Matrix4 Rotations...");
  Matrix4 copy(matrix);

  Matrix4 answer(
    0.0f, 1.0f, -2.0f, 3.0f,
    4.0f, 5.0f, -6.0f, 7.0f,
    8.0f, 9.0f, -10.0f, 11.0f,
    12.0f, 13.0f, -14.0f, 15.0f
  );


  fmt::print("rotateX( 90.0f)... ");
  copy.rotateX(90);
  if (compare_result(copy, answer)) {
    fmt::println("\e[32m[SUCCESS]:\e[0m");
  } else {
    fmt::println("\e[31m[FAIL]:\e[0m");
  }

  fmt::print("rotateX(-90.0f)... ");
  copy.rotateX(-90.0f);
  if (compare_result(copy, matrix)) {
    fmt::println("\e[32m[SUCCESS]:\e[0m");
  } else {
    fmt::println("\e[31m[FAIL]:\e[0m");
  }
}

void test::matrix4() {
  Matrix4 matrix = {
     0.0f,  1.0f,  2.0f,  3.0f,
     4.0f,  5.0f,  6.0f,  7.0f,
     8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f
  };
  
  test_rotation(matrix);
}
