#ifndef MATRIX_CPP_H
#define MATRIX_CPP_H

#include <gtest/gtest.h>

#include <initializer_list>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  Matrix(int, int);
  Matrix(std::initializer_list<std::initializer_list<int>>);
  Matrix(const Matrix&);
  ~Matrix();
  void SetElement(int, int, double);
  bool EqMatrix(const Matrix&);
  void Add(const Matrix&);
  void Sub(const Matrix&);
  void operator=(const Matrix&);
  void MultMatrix(const Matrix&);
  Matrix Transpose();
  Matrix Minor(int, int);
  double Determinant();
};

#endif
