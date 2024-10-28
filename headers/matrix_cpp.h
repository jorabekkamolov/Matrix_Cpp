#ifndef MATRIX_CPP_H
#define MATRIX_CPP_H

#include <iostream>
#include <initializer_list>
#include <gtest/gtest.h>

class Matrix {
  private:
    int rows_, cols_;
    double** matrix_;
  public:
    Matrix(int, int);
    Matrix(std::initializer_list<std::initializer_list<int>>);
    ~Matrix();
    void SetElement(int, int, double);
    double get(int, int);
};

#endif
