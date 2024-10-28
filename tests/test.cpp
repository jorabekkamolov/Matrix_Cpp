#include "../headers/matrix_cpp.h"

TEST(Matrix_test, Init){
  Matrix mat(2,2);
  mat.SetElement(0, 0, 12.0);

  EXPECT_EQ(mat.get(0, 0), 12.0);
}

int main(int argc, char* argv[]){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
