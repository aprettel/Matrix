#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Matrix1x1, constructor1x1_true) {
  S21Matrix matrix_A;
  ASSERT_TRUE(matrix_A.GetRows() == 2);
  ASSERT_TRUE(matrix_A.GetCols() == 2);
  ASSERT_TRUE(matrix_A(0, 0) == 0);
}

TEST(MatrixSetRows, setrows_true) {
  S21Matrix matrix_A(2, 3);
  matrix_A.SetRows(4);
  ASSERT_TRUE(matrix_A.GetRows() == 4);
}

TEST(MatrixSetRows, setrows_true_2) {
  S21Matrix matrix_A(2, 3);
  matrix_A.SetRows(1);
  ASSERT_TRUE(matrix_A.GetRows() == 1);
}

TEST(MatrixSetRows, setrows_throw) {
  S21Matrix matrix_A(2, 3);
  ASSERT_THROW(matrix_A.SetRows(0), std::invalid_argument);
}

TEST(MatrixSetCols, setcols_true) {
  S21Matrix matrix_A(2, 3);
  matrix_A.SetCols(5);
  ASSERT_TRUE(matrix_A.GetCols() == 5);
}

TEST(MatrixSetCols, setcols_true_2) {
  S21Matrix matrix_A(2, 3);
  matrix_A.SetCols(2);
  ASSERT_TRUE(matrix_A.GetCols() == 2);
}

TEST(MatrixSetCols, setcols_throw) {
  S21Matrix matrix_A(2, 3);
  ASSERT_THROW(matrix_A.SetCols(0), std::invalid_argument);
}

TEST(Copy, copy_true) {
  S21Matrix matrix_A(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  S21Matrix matrix_B(matrix_A);
  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_B(i, j), 1e-07);
    }
  }
}

TEST(Out, out_of_range) {
  S21Matrix matrix(0, 0);
  ASSERT_THROW(matrix(0, 0), std::out_of_range);
}

TEST(Move, move_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 1.45;
  matrix_B(0, 1) = 3;
  matrix_B(1, 0) = 7.1;
  matrix_B(1, 1) = 9;

  S21Matrix matrix_R(std::move(matrix_A));

  ASSERT_TRUE(matrix_R == matrix_B);
  ASSERT_FALSE(matrix_R == matrix_A);

  matrix_A.delete_matrix();
  ASSERT_FALSE(matrix_A.is_create());

  ASSERT_NEAR(matrix_B(0, 0), 1.45, 0.001);
  ASSERT_NEAR(matrix_B(0, 1), 3, 0.001);
  ASSERT_NEAR(matrix_B(1, 0), 7.1, 0.001);
  ASSERT_NEAR(matrix_B(1, 1), 9, 0.001);
}

TEST(Eq, eq_true) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B = matrix_A;

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_B(i, j), 1e-07);
    }
  }
}

TEST(PlusEqual, plusEq_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 3.45;
  matrix_R(0, 1) = 7.34;
  matrix_R(1, 0) = 15.1;
  matrix_R(1, 1) = 10;

  matrix_A = (matrix_A += matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(PlusEqual, plusEq_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 5.45;
  matrix_R(0, 1) = -7.34;
  matrix_R(1, 0) = 1.1;
  matrix_R(1, 1) = 10;

  ASSERT_FALSE((matrix_A += matrix_B) == matrix_R);
}

TEST(Plus, plus_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 3.45;
  matrix_R(0, 1) = 7.34;
  matrix_R(1, 0) = 15.1;
  matrix_R(1, 1) = 10;

  matrix_A = (matrix_A + matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Plus, plus_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 5.45;
  matrix_R(0, 1) = -7.34;
  matrix_R(1, 0) = 1.1;
  matrix_R(1, 1) = 10;

  ASSERT_FALSE((matrix_A + matrix_B) == matrix_R);
}

TEST(MinusEqual, minusEq_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 0.45;
  matrix_R(0, 1) = -1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  matrix_A = (matrix_A -= matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(MinusEqual, minusEq_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 42.45;
  matrix_R(0, 1) = 1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  ASSERT_FALSE((matrix_A -= matrix_B) == matrix_R);
}

TEST(Minus, minus_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 0.45;
  matrix_R(0, 1) = -1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  matrix_A = (matrix_A - matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Minus, minus_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 42.45;
  matrix_R(0, 1) = 1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  ASSERT_FALSE((matrix_A - matrix_B) == matrix_R);
}

TEST(MulEqual, mulEq_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = -2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 28.9;
  matrix_R(0, 1) = -7.633;
  matrix_R(1, 0) = 57.8;
  matrix_R(1, 1) = 39.814;

  matrix_A = (matrix_A *= matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(MulEqual, mulEq_true_2) {
  S21Matrix matrix_A(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_R(0, 0) = 4.9;
  matrix_R(0, 1) = -6;
  matrix_R(1, 0) = -14.2;
  matrix_R(1, 1) = -18;

  matrix_A = (matrix_A *= -2);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(MulEqual, mulEq_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 4.9;
  matrix_R(0, 1) = -13.02;
  matrix_R(1, 0) = 56.8;
  matrix_R(1, 1) = 9;

  ASSERT_FALSE((matrix_A *= matrix_B) == matrix_R);
}

TEST(Mul, mul_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = -2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 28.9;
  matrix_R(0, 1) = -7.633;
  matrix_R(1, 0) = 57.8;
  matrix_R(1, 1) = 39.814;

  matrix_A = (matrix_A * matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Mul, mul_true_2) {
  S21Matrix matrix_A(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_R(0, 0) = 4.9;
  matrix_R(0, 1) = -6;
  matrix_R(1, 0) = -14.2;
  matrix_R(1, 1) = -18;

  matrix_A = (matrix_A * -2);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Mul, mul_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 4.9;
  matrix_R(0, 1) = -13.02;
  matrix_R(1, 0) = 56.8;
  matrix_R(1, 1) = 9;

  ASSERT_FALSE((matrix_A * matrix_B) == matrix_R);
}

TEST(Equal, equal_true) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 1.55;
  matrix_B(0, 1) = 3;
  matrix_B(0, 2) = 5;
  matrix_B(1, 0) = 7;
  matrix_B(1, 1) = 9;
  matrix_B(1, 2) = 2.34;
  matrix_B(2, 0) = 4;
  matrix_B(2, 1) = 6;
  matrix_B(2, 2) = 8;

  matrix_A.EqMatrix(matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_B(i, j), 1e-07);
    }
  }
}

TEST(Equal, equal_false) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4;
  matrix_B(0, 2) = 6;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;
  matrix_B(1, 2) = 3;
  matrix_B(2, 0) = 5;
  matrix_B(2, 1) = 7;
  matrix_B(2, 2) = 9;

  ASSERT_FALSE(matrix_A.EqMatrix(matrix_B));
}

TEST(Equal, equal_throw) {
  S21Matrix matrix_A(2, 3), matrix_B(3, 2);
  ASSERT_FALSE(matrix_A.EqMatrix(matrix_B));
}

TEST(Sum, sum_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 3.45;
  matrix_R(0, 1) = 7.34;
  matrix_R(1, 0) = 15.1;
  matrix_R(1, 1) = 10;

  matrix_A.SumMatrix(matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Sum, sum_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 1.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 3;
  matrix_R(0, 1) = 7;
  matrix_R(1, 0) = 15.1;
  matrix_R(1, 1) = 10;

  matrix_A.SumMatrix(matrix_B);
  ASSERT_FALSE(matrix_A == matrix_R);
}

TEST(Sum, sum_throw) {
  S21Matrix matrix_A(2, 3), matrix_B(3, 2), matrix_R(3, 3);
  ASSERT_THROW(matrix_A.SumMatrix(matrix_B), std::invalid_argument);
}

TEST(Sub, sub_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 0.45;
  matrix_R(0, 1) = -1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  matrix_A.SubMatrix(matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Sub, sub_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = -0.45;
  matrix_R(0, 1) = -1.34;
  matrix_R(1, 0) = -0.9;
  matrix_R(1, 1) = 8;

  matrix_A.SubMatrix(matrix_B);
  ASSERT_FALSE(matrix_A == matrix_R);
}

TEST(Sub, sub_throw) {
  S21Matrix matrix_A(2, 3), matrix_B(3, 2), matrix_R(3, 3);
  ASSERT_THROW(matrix_A.SubMatrix(matrix_B), std::invalid_argument);
}

TEST(MulNum, mul_N_true) {
  S21Matrix matrix_A(2, 2), matrix_R(2, 2);
  double num = 2.3;
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_R(0, 0) = -5.635;
  matrix_R(0, 1) = 6.9;
  matrix_R(1, 0) = 16.33;
  matrix_R(1, 1) = 20.7;

  matrix_A.MulNumber(num);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(MulNum, mul_N_false) {
  S21Matrix matrix_A(2, 2), matrix_R(2, 2);
  double num = -2.3;
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_R(0, 0) = 5.635;
  matrix_R(0, 1) = -6.9;
  matrix_R(1, 0) = -16.33;
  matrix_R(1, 1) = 20.7;

  matrix_A.MulNumber(num);
  ASSERT_FALSE(matrix_A == matrix_R);
}

TEST(Mul, mul_M_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = -2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = -2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 28.9;
  matrix_R(0, 1) = -7.633;
  matrix_R(1, 0) = 57.8;
  matrix_R(1, 1) = 39.814;

  matrix_A.MulMatrix(matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Mul, mul_M_true_2) {
  S21Matrix matrix_A(3, 2), matrix_B(2, 3), matrix_R(3, 3);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(1, 0) = 3;
  matrix_A(1, 1) = 4;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = 6;

  matrix_B(0, 0) = 1;
  matrix_B(0, 1) = 2;
  matrix_B(0, 2) = 3;
  matrix_B(1, 0) = 4;
  matrix_B(1, 1) = 5;
  matrix_B(1, 2) = 6;

  matrix_R(0, 0) = 9;
  matrix_R(0, 1) = 12;
  matrix_R(0, 2) = 15;
  matrix_R(1, 0) = 19;
  matrix_R(1, 1) = 26;
  matrix_R(1, 2) = 33;
  matrix_R(2, 0) = 29;
  matrix_R(2, 1) = 40;
  matrix_R(2, 2) = 51;

  matrix_A.MulMatrix(matrix_B);

  for (int i = 0; i < matrix_A.GetRows(); i++) {
    for (int j = 0; j < matrix_A.GetCols(); j++) {
      ASSERT_NEAR(matrix_A(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Mul, mul_M_false) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2), matrix_R(2, 2);
  matrix_A(0, 0) = 2.45;
  matrix_A(0, 1) = 3;
  matrix_A(1, 0) = 7.1;
  matrix_A(1, 1) = 9;

  matrix_B(0, 0) = 2;
  matrix_B(0, 1) = 4.34;
  matrix_B(1, 0) = 8;
  matrix_B(1, 1) = 1;

  matrix_R(0, 0) = 4.9;
  matrix_R(0, 1) = -13.02;
  matrix_R(1, 0) = 56.8;
  matrix_R(1, 1) = 9;

  matrix_A.MulMatrix(matrix_B);
  ASSERT_FALSE(matrix_A == matrix_R);
}

TEST(Mul, mul_M_throw) {
  S21Matrix matrix_A(3, 2), matrix_B(3, 2);
  ASSERT_THROW(matrix_A.MulMatrix(matrix_B), std::invalid_argument);
}

TEST(Transpose, transpose_true) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 1.55;
  matrix_B(0, 1) = 7;
  matrix_B(0, 2) = 4;
  matrix_B(1, 0) = 3;
  matrix_B(1, 1) = 9;
  matrix_B(1, 2) = 6;
  matrix_B(2, 0) = 5;
  matrix_B(2, 1) = 2.34;
  matrix_B(2, 2) = 8;

  S21Matrix matrix_R(matrix_A.Transpose());

  for (int i = 0; i < matrix_R.GetRows(); i++) {
    for (int j = 0; j < matrix_R.GetCols(); j++) {
      ASSERT_NEAR(matrix_B(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Transpose, transpose_false) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 1.55;
  matrix_B(0, 1) = 3;
  matrix_B(0, 2) = 5;
  matrix_B(1, 0) = 7;
  matrix_B(1, 1) = 9;
  matrix_B(1, 2) = 2.34;
  matrix_B(2, 0) = 4;
  matrix_B(2, 1) = 6;
  matrix_B(2, 2) = 8;

  S21Matrix matrix_R(matrix_A.Transpose());
  ASSERT_FALSE(matrix_R == matrix_B);
}

TEST(CalcComplements, calcComplements_true) {
  S21Matrix matrix_A(1, 1), matrix_B(1, 1);
  matrix_A(0, 0) = 1.55;

  matrix_B(0, 0) = 1;

  S21Matrix matrix_R(matrix_A.CalcComplements());

  for (int i = 0; i < matrix_R.GetRows(); i++) {
    for (int j = 0; j < matrix_R.GetCols(); j++) {
      ASSERT_NEAR(matrix_B(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(CalcComplements, calcComplements_true_2) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(0, 2) = 3;
  matrix_A(1, 0) = 0;
  matrix_A(1, 1) = 4;
  matrix_A(1, 2) = 2;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = 2;
  matrix_A(2, 2) = 1;

  matrix_B(0, 0) = 0;
  matrix_B(0, 1) = 10;
  matrix_B(0, 2) = -20;
  matrix_B(1, 0) = 4;
  matrix_B(1, 1) = -14;
  matrix_B(1, 2) = 8;
  matrix_B(2, 0) = -8;
  matrix_B(2, 1) = -2;
  matrix_B(2, 2) = 4;

  S21Matrix matrix_R(matrix_A.CalcComplements());

  for (int i = 0; i < matrix_R.GetRows(); i++) {
    for (int j = 0; j < matrix_R.GetCols(); j++) {
      ASSERT_NEAR(matrix_B(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(CalcComplements, calcComplements_false) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 1.55;
  matrix_B(0, 1) = 3;
  matrix_B(0, 2) = 5;
  matrix_B(1, 0) = 7;
  matrix_B(1, 1) = 9;
  matrix_B(1, 2) = 2.34;
  matrix_B(2, 0) = 4;
  matrix_B(2, 1) = 6;
  matrix_B(2, 2) = 8;

  S21Matrix matrix_R(matrix_A.CalcComplements());
  ASSERT_FALSE(matrix_R == matrix_B);
}

TEST(CalcComplements, calcComplements_throw) {
  S21Matrix matrix_A(3, 2);
  ASSERT_THROW(matrix_A.CalcComplements(), std::invalid_argument);
}

TEST(Minor, minor_true) {
  S21Matrix matrix_A(3, 3), matrix_B(2, 2);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(0, 2) = 3;
  matrix_A(1, 0) = 4;
  matrix_A(1, 1) = 5;
  matrix_A(1, 2) = 6;
  matrix_A(2, 0) = 7;
  matrix_A(2, 1) = 8;
  matrix_A(2, 2) = 9;

  matrix_B(0, 0) = 1;
  matrix_B(0, 1) = 3;
  matrix_B(1, 0) = 7;
  matrix_B(1, 1) = 9;

  for (int i = 0; i < matrix_B.GetRows(); i++) {
    for (int j = 0; j < matrix_B.GetCols(); j++) {
      ASSERT_NEAR(matrix_A.Minor(matrix_A, 1, 1)(i, j), matrix_B(i, j), 1e-07);
    }
  }
}

TEST(Minor, minor_false) {
  S21Matrix matrix_A(3, 3), matrix_B(2, 2);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(0, 2) = 3;
  matrix_A(1, 0) = 4;
  matrix_A(1, 1) = 5;
  matrix_A(1, 2) = 6;
  matrix_A(2, 0) = 7;
  matrix_A(2, 1) = 8;
  matrix_A(2, 2) = 9;

  matrix_B(0, 0) = 1;
  matrix_B(0, 1) = 3;

  ASSERT_FALSE(matrix_A.Minor(matrix_A, 1, 1) == matrix_B);
}

TEST(Determinant, determinant_true) {
  S21Matrix matrix_A(1, 1);
  matrix_A(0, 0) = 1.2345678;
  ASSERT_NEAR(matrix_A.Determinant(), 1.2345678, 1e-07);
}

TEST(Determinant, determinant_true_2) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(1, 0) = 3;
  matrix_A(1, 1) = 4;

  ASSERT_NEAR(matrix_A.Determinant(), -2, 1e-07);
}

TEST(Determinant, determinant_throw) {
  S21Matrix matrix_A(3, 2);
  ASSERT_THROW(matrix_A.Determinant(), std::invalid_argument);
}

TEST(Inverse, inverse_true) {
  S21Matrix matrix_A(2, 2), matrix_B(2, 2);
  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(1, 0) = 3;
  matrix_A(1, 1) = 4;

  matrix_B(0, 0) = -2;
  matrix_B(0, 1) = 1;
  matrix_B(1, 0) = 1.5;
  matrix_B(1, 1) = -0.5;

  S21Matrix matrix_R(matrix_A.InverseMatrix());

  for (int i = 0; i < matrix_R.GetRows(); i++) {
    for (int j = 0; j < matrix_R.GetCols(); j++) {
      ASSERT_NEAR(matrix_B(i, j), matrix_R(i, j), 1e-07);
    }
  }
}

TEST(Inverse, inverse_false) {
  S21Matrix matrix_A(3, 3), matrix_B(3, 3);
  matrix_A(0, 0) = 1.55;
  matrix_A(0, 1) = 3;
  matrix_A(0, 2) = 5;
  matrix_A(1, 0) = 7;
  matrix_A(1, 1) = 9;
  matrix_A(1, 2) = 2.34;
  matrix_A(2, 0) = 4;
  matrix_A(2, 1) = 6;
  matrix_A(2, 2) = 8;

  matrix_B(0, 0) = 1.55;
  matrix_B(0, 1) = 3;
  matrix_B(0, 2) = 5;
  matrix_B(1, 0) = 7;
  matrix_B(1, 1) = 9;
  matrix_B(1, 2) = 2.34;
  matrix_B(2, 0) = 4;
  matrix_B(2, 1) = 6;
  matrix_B(2, 2) = 8;

  S21Matrix matrix_R(matrix_A.InverseMatrix());
  ASSERT_FALSE(matrix_R == matrix_B);
}

TEST(Inverse, inverse_throw) {
  S21Matrix matrix_A(3, 2);
  ASSERT_THROW(matrix_A.InverseMatrix(), std::invalid_argument);
}

int main() {
  ::testing::InitGoogleTest();
#ifdef __APPLE__
  free(__cxxabiv1::__cxa_get_globals());
#endif
  return RUN_ALL_TESTS();
}