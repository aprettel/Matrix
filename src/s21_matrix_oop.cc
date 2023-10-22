#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : matrix_(nullptr), rows_(2), cols_(2) {
  create_matrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : matrix_(other.matrix_), rows_(other.rows_), cols_(other.cols_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { this->delete_matrix(); }

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix tmp = *this;
  tmp += other;
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix tmp = *this;
  tmp -= other;
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix tmp = *this;
  tmp *= other;
  return tmp;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix tmp = *this;
  tmp *= num;
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->delete_matrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      this->matrix_[i] = new double[cols_];
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[i][j];
}

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Number of rows must be greater than zero");
  }
  S21Matrix tmp(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (rows < rows_) {
        tmp.matrix_[i][j] = matrix_[i][j];
      } else {
        tmp.matrix_[i][j] = 0;
      }
    }
  }
  *this = tmp;
}

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Number of rows must be greater than zero");
  }
  S21Matrix tmp(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (cols < cols_) {
        tmp.matrix_[i][j] = matrix_[i][j];
      } else {
        tmp.matrix_[i][j] = 0;
      }
    }
  }
  *this = tmp;
}

void S21Matrix::create_matrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::delete_matrix() {
  if (is_create()) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

bool S21Matrix::is_create() { return matrix_ != nullptr; }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different size of matrix!");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different size of matrix!");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Different size of matrix!");
  } else {
    S21Matrix tmp(rows_, other.cols_);
    for (int i = 0; i < tmp.rows_; ++i) {
      for (int j = 0; j < tmp.cols_; ++j) {
        tmp.matrix_[i][j] = 0;
        for (int k = 0; k < cols_; ++k) {
          tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = tmp;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Different size of matrix!");
  }
  S21Matrix tmp(cols_, rows_);
  if (rows_ == 1 && cols_ == 1) {
    tmp.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < tmp.rows_; ++i) {
      for (int j = 0; j < tmp.cols_; ++j) {
        S21Matrix temp = Minor(*this, i, j);
        tmp.matrix_[i][j] = temp.Determinant() * pow(-1, i + j);
      }
    }
  }
  return tmp;
}

S21Matrix S21Matrix::Minor(const S21Matrix& other, int minor_r, int minor_c) {
  S21Matrix minor(other.rows_ - 1, other.cols_ - 1);
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      if (i != minor_r && j != minor_c) {
        if (i > minor_r && j > minor_c) {
          minor.matrix_[i - 1][j - 1] = other.matrix_[i][j];
        } else if (i > minor_r && j < minor_c) {
          minor.matrix_[i - 1][j] = other.matrix_[i][j];
        } else if (i < minor_r && j > minor_c) {
          minor.matrix_[i][j - 1] = other.matrix_[i][j];
        } else {
          minor.matrix_[i][j] = other.matrix_[i][j];
        }
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Different size of matrix!");
  }
  double determ = 0.0;
  if (rows_ == 1 && cols_ == 1) {
    determ = matrix_[0][0];
  } else if (rows_ == 2 && cols_ == 2) {
    determ = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int j = 1; j <= cols_; ++j) {
      S21Matrix tmp = Minor(*this, 0, j - 1);
      determ += pow(-1, 1 + j) * matrix_[0][j - 1] * tmp.Determinant();
    }
  }
  return determ;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_ || cols_ != rows_) {
    throw std::invalid_argument("Different size of matrix!");
  }
  double determ = Determinant();
  S21Matrix tmp(rows_, cols_);
  S21Matrix temp = CalcComplements();
  S21Matrix trans = temp.Transpose();

  tmp = trans;
  tmp.MulNumber(1.0 / determ);
  return tmp;
}
