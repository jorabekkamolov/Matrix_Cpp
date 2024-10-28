#include "../headers/matrix_cpp.h"

Matrix::Matrix(int r, int c): rows_(r), cols_(c) {
  matrix_ = new double*[rows_];
  for(int i = 0; i < rows_; i++){
    matrix_[i] = new double[cols_]{0.0};
  }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> list){
  rows_ = list.size();
  cols_ = list.begin()->size();

  matrix_ = new double*[rows_];
  int i = 0;
  for(const auto& row : list){
    matrix_[i] = new double[cols_];
    int j = 0;
    for(const auto& value : row){
      matrix_[i][j++] = static_cast<double>(value);
    }
    ++i;
  }
}

Matrix::~Matrix() {
  for(int i = 0; i < rows_; i++){
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void Matrix::SetElement(int r, int c, double value){
  if(r < rows_ && c < cols_){
    matrix_[r][c] = value;
  }
}

double Matrix::get(int r, int c){
  return matrix_[r][c];
}