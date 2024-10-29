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

Matrix::Matrix(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
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

bool Matrix::EqMatrix(const Matrix& other) {
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

void Matrix::Add(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Row or Cols no equal!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::Sub(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Row or Cols no equal!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;

    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

void Matrix::MultMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("No eq rows_ and cols_");
  }
  Matrix answer(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double temp = 0;
      for (int t = 0; t < cols_; t++) {
        temp += (matrix_[i][t] * other.matrix_[t][j]);
      }
      answer.matrix_[i][j] = temp;
    }
  }
  *this = answer;
}

Matrix Matrix::Transpose() {
  Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}

Matrix Matrix::Minor(int r, int c) {
  Matrix minor(rows_ - 1, cols_ - 1);
  int minor_r = 0, minor_c = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == r) {
      continue;
    }
    minor_c = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == c) {
        continue;
      }
      minor.matrix_[minor_r][minor_c++] = matrix_[i][j];
    }
    minor_r++;
  }
  return minor;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: Matrix is not square");
  }

  if (rows_ == 2 && cols_ == 2) {
    return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  }

  double det = 0.0;
  for (int i = 0; i < cols_; i++) {
    Matrix minor_matrix = Minor(0, i);
    double sign = (i % 2 == 0) ? 1.0 : -1.0;
    det += sign * matrix_[0][i] * minor_matrix.Determinant();
  }
  return det;
}