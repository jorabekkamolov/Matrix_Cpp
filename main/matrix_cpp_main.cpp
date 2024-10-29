#include "../headers/matrix_cpp.h"

Matrix::Matrix(int r, int c) : rows_(r), cols_(c) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{0.0};
  }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> list) {
  rows_ = list.size();
  cols_ = list.begin()->size();

  matrix_ = new double*[rows_];
  int i = 0;
  for (const auto& row : list) {
    matrix_[i] = new double[cols_];
    int j = 0;
    for (const auto& value : row) {
      matrix_[i][j++] = static_cast<double>(value);
    }
    ++i;
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void Matrix::SetElement(int r, int c, double value) {
  if (r < rows_ && c < cols_) {
    matrix_[r][c] = value;
  }
}

bool Matrix::EqMatrix(Matrix& other) {
  bool answer = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    answer = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          answer = false;
        }
      }
    }
  }
  return answer;
}

void Matrix::Add(Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Row or Cols no equal!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::Sub(Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Row or Cols no equal!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}