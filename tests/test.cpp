#include "../headers/matrix_cpp.h"

TEST(Matrix_test, Eq1) {
  Matrix mat1(2, 2);
  Matrix mat2(2, 2);

  mat1.SetElement(0, 0, 12.0);
  mat1.SetElement(0, 1, 13.0);
  mat2.SetElement(0, 0, 12.0);
  mat2.SetElement(0, 1, 13.0);
  EXPECT_EQ(mat1.EqMatrix(mat2), true);
}

TEST(Matrix_test, Eq2) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2(2, 2);

  EXPECT_EQ(mat1.EqMatrix(mat2), false);
}

TEST(Matrix_test, Eq3) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2 = {{1, 2, 3}, {4, 5, 7}};

  EXPECT_EQ(mat1.EqMatrix(mat2), false);
}

TEST(Matrix_test, Add1) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2 = {{1, 2, 3}, {4, 5, 7}};
  mat1.Add(mat2);
  Matrix mat3 = {{2, 4, 6}, {8, 10, 13}};
  EXPECT_EQ(mat1.EqMatrix(mat3), true);
}

TEST(Matrix_test, Add2) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2 = {{1, 2, 3}, {4, 5, 7}, {1, 3, 7}};
  EXPECT_THROW(mat1.Add(mat2), std::invalid_argument);
}

TEST(Matrix_test, Sub1) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2 = {{1, 2, 3}, {4, 5, 7}, {1, 3, 7}};
  EXPECT_THROW(mat1.Sub(mat2), std::invalid_argument);
}

TEST(Matrix_test, Sub2) {
  Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};
  Matrix mat2 = {{1, 2, 3}, {4, 5, 7}};
  mat1.Sub(mat2);
  Matrix mat3 = {{0, 0, 0}, {0, 0, -1}};
  EXPECT_EQ(mat1.EqMatrix(mat3), true);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
