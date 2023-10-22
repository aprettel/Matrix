#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_
#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  double** matrix_;
  int rows_;
  int cols_;

 public:
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix Minor(const S21Matrix& other, int minor_r, int minor_j);
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j);

  void create_matrix();
  void delete_matrix();
  bool is_create();

  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);
};

#endif  // S21_MATRIX_OOP_H_