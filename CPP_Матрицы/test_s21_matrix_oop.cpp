#include <gtest/gtest.h>

#include <cstdlib>

#include "s21_matrix_oop.h"

static bool throw_bad_alloc = false;

void* operator new(std::size_t size) {
  if (throw_bad_alloc) {
    throw std::bad_alloc();
  }
  return std::malloc(size);
}

void operator delete(void* ptr) noexcept { std::free(ptr); }

void operator delete(void* ptr, std::size_t) noexcept { std::free(ptr); }

void* operator new[](std::size_t size) {
  if (throw_bad_alloc) {
    throw std::bad_alloc();
  }
  return std::malloc(size);
}

void operator delete[](void* ptr) noexcept { std::free(ptr); }

void operator delete[](void* ptr, std::size_t) noexcept { std::free(ptr); }

TEST(MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(MatrixTest, Constructor) {
  S21Matrix m(2, 2);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
}

TEST(MatrixTest, FailConstructor) {
  EXPECT_THROW(S21Matrix m(-2, 2), std::invalid_argument);
}

TEST(MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 2);
  S21Matrix m2(m1);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
  m1(0, 0) = 21;
  m2(0, 0) = 12;
  EXPECT_NE(m1(0, 0), m2(0, 0));
}

TEST(MatrixTest, MoveConstructor) {
  S21Matrix m1(2, 2);
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(MatrixTest, BadAllocTest) {
  throw_bad_alloc = true;

  EXPECT_THROW({ S21Matrix matrix(5, 5); }, std::bad_alloc);

  throw_bad_alloc = false;
}

TEST(MatrixTest, BadAllocBasicTest) {
  throw_bad_alloc = true;

  EXPECT_THROW({ S21Matrix matrix; }, std::bad_alloc);

  throw_bad_alloc = false;
}

TEST(MatrixTest, CopyConstructorBadAllocOnFirstNew) {
  S21Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(1, 0) = 3.0;
  original(1, 1) = 4.0;

  throw_bad_alloc = true;

  EXPECT_THROW({ S21Matrix copy(original); }, std::bad_alloc);

  throw_bad_alloc = false;

  EXPECT_EQ(original(0, 0), 1.0);
  EXPECT_EQ(original(0, 1), 2.0);
  EXPECT_EQ(original(1, 0), 3.0);
  EXPECT_EQ(original(1, 1), 4.0);
}

TEST(MatrixTest, SetRowsLess) {
  S21Matrix matrix(4, 4);
  matrix.SetRows(2);
  EXPECT_EQ(matrix.GetRows(), 2);
}

TEST(MatrixTest, SetRowsEqual) {
  S21Matrix matrix(4, 4);
  matrix.SetRows(4);
  EXPECT_EQ(matrix.GetRows(), 4);
}

TEST(MatrixTest, SetRowsMore) {
  S21Matrix matrix(4, 4);
  matrix.SetRows(6);
  EXPECT_EQ(matrix.GetRows(), 6);
  EXPECT_EQ(matrix(5, 3), 0);
}

TEST(MatrixTest, SetRowsNegative) {
  S21Matrix matrix(4, 4);
  EXPECT_THROW(matrix.SetRows(-3), std::invalid_argument);
  EXPECT_EQ(matrix.GetRows(), 4);
}

TEST(MatrixTest, SetColsLess) {
  S21Matrix matrix(4, 4);
  matrix.SetCols(2);
  EXPECT_EQ(matrix.GetCols(), 2);
}

TEST(MatrixTest, SetColsEqual) {
  S21Matrix matrix(4, 4);
  matrix.SetCols(4);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(MatrixTest, SetColsMore) {
  S21Matrix matrix(4, 4);
  matrix.SetCols(6);
  EXPECT_EQ(matrix.GetCols(), 6);
  EXPECT_EQ(matrix(3, 5), 0);
}

TEST(MatrixTest, SetColsNegative) {
  S21Matrix matrix(4, 4);
  EXPECT_THROW(matrix.SetCols(-3), std::invalid_argument);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(MatrixTest, EqualDifferent) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(3, 3);
  EXPECT_EQ(matrix.EqMatrix(other_matrix), false);
}

TEST(MatrixTest, EqualDifferentValues) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(4, 4);
  matrix(0, 0) = 3.0;
  EXPECT_EQ(matrix.EqMatrix(other_matrix), false);
}

TEST(MatrixTest, EqualEqual) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(4, 4);
  matrix(2, 1) = 4.0;
  other_matrix(2, 1) = 4.0;
  EXPECT_EQ(matrix.EqMatrix(other_matrix), true);
}

TEST(MatrixTest, SumExep) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(3, 3);
  matrix(2, 1) = 4.0;
  other_matrix(2, 1) = 4.0;

  EXPECT_THROW(matrix.SumMatrix(other_matrix), std::invalid_argument);
}

TEST(MatrixTest, SumSum) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(4, 4);
  matrix(2, 1) = 4.0;
  other_matrix(2, 1) = 4.0;
  matrix.SumMatrix(other_matrix);
  EXPECT_EQ(matrix(2, 1), 8.0);
}

TEST(MatrixTest, SubExep) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(3, 3);
  matrix(2, 1) = 4.0;
  other_matrix(2, 1) = 4.0;

  EXPECT_THROW(matrix.SubMatrix(other_matrix), std::invalid_argument);
}

TEST(MatrixTest, SubSub) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(4, 4);
  matrix(2, 1) = 7.0;
  other_matrix(2, 1) = 4.0;
  matrix.SubMatrix(other_matrix);
  EXPECT_EQ(matrix(2, 1), 3.0);
}

TEST(MatrixTest, MulNumber) {
  S21Matrix matrix(4, 4);
  matrix(2, 1) = 7.0;
  double num = 2.0;
  matrix.MulNumber(num);
  EXPECT_EQ(matrix(2, 1), 14.0);
}

TEST(MatrixTest, MulMatrix) {
  S21Matrix matrix(3, 3);
  S21Matrix other_matrix(3, 3);
  matrix(0, 0) = 3.2;
  matrix(0, 1) = 1.4;
  matrix(0, 2) = 2.5;
  other_matrix(0, 0) = 1.5;
  other_matrix(0, 1) = 3.1;
  matrix.MulMatrix(other_matrix);
  EXPECT_NEAR(matrix(0, 0), 4.8, epsilon);
  EXPECT_NEAR(matrix(0, 1), 9.92, epsilon);
}

TEST(MatrixTest, MulExep) {
  S21Matrix matrix(4, 4);
  S21Matrix other_matrix(3, 4);
  EXPECT_THROW(matrix.MulMatrix(other_matrix), std::invalid_argument);
}

TEST(MatrixTest, Transpose) {
  S21Matrix matrix(4, 3);
  S21Matrix transposed;
  matrix(0, 0) = 3.2;
  matrix(0, 1) = 1.4;
  matrix(0, 2) = 2.5;
  transposed = matrix.Transpose();
  EXPECT_EQ(transposed(0, 0), 3.2);
  EXPECT_EQ(transposed(1, 0), 1.4);
  EXPECT_EQ(transposed(2, 0), 2.5);
}

TEST(MatrixTest, Determinant) {
  S21Matrix matrix;
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  EXPECT_NEAR(matrix.Determinant(), -1, epsilon);
}

TEST(MatrixTest, DeterminantWrongSize) {
  S21Matrix matrix(4, 3);
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

TEST(MatrixTest, DeterminantSmall) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 2;

  EXPECT_NEAR(matrix.Determinant(), 2, epsilon);
}

TEST(MatrixTest, CalcComplementsWrongSize) {
  S21Matrix matrix(4, 3);
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  EXPECT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

TEST(MatrixTest, CalcComplementsSmall) {
  S21Matrix matrix(1, 1);
  S21Matrix complements;
  matrix(0, 0) = 2;
  complements = matrix.CalcComplements();
  EXPECT_NEAR(complements(0, 0), 1, epsilon);
  EXPECT_EQ(complements.GetCols(), 1);
  EXPECT_EQ(complements.GetRows(), 1);
}

TEST(MatrixTest, CalcComplementsBig) {
  S21Matrix matrix(5, 5);
  matrix(0, 0) = 7.23455;
  matrix(0, 1) = 2.34562;
  matrix(0, 2) = 4.35263;
  matrix(0, 3) = 2.34623;
  matrix(0, 4) = 4.53452;
  matrix(1, 0) = 3.62365;
  matrix(1, 1) = 2.35846;
  matrix(1, 2) = 1.25651;
  matrix(1, 3) = 1.23196;
  matrix(1, 4) = 9.41528;
  matrix(2, 0) = 1.48255;
  matrix(2, 1) = 1.45923;
  matrix(2, 2) = 9.97854;
  matrix(2, 3) = 4.56378;
  matrix(2, 4) = 3.79864;
  matrix(3, 0) = 6.76854;
  matrix(3, 1) = 7.86945;
  matrix(3, 2) = 7.98645;
  matrix(3, 3) = 8.96722;
  matrix(3, 4) = 6.68456;
  matrix(4, 0) = 5.56645;
  matrix(4, 1) = 6.98697;
  matrix(4, 2) = 6.78695;
  matrix(4, 3) = 6.42368;
  matrix(4, 4) = 7.56756;
  S21Matrix complements = matrix.CalcComplements();
  EXPECT_NEAR(complements(0, 0), -620.6435278, epsilon);
  EXPECT_NEAR(complements(0, 1), 87.8118568, epsilon);
  EXPECT_NEAR(complements(0, 2), -180.6645081, epsilon);
  EXPECT_NEAR(complements(0, 3), 412.9515219, epsilon);
  EXPECT_NEAR(complements(0, 4), 186.9472997, epsilon);
  EXPECT_NEAR(complements(1, 0), 71.56336875, epsilon);
  EXPECT_NEAR(complements(1, 1), 742.6650756, epsilon);
  EXPECT_NEAR(complements(1, 2), 378.6163682, epsilon);
  EXPECT_NEAR(complements(1, 3), -652.0780126, epsilon);
  EXPECT_NEAR(complements(1, 4), -524.3754116, epsilon);
  EXPECT_NEAR(complements(2, 0), 167.1845403, epsilon);
  EXPECT_NEAR(complements(2, 1), 381.3013321, epsilon);
  EXPECT_NEAR(complements(2, 2), -323.5987408, epsilon);
  EXPECT_NEAR(complements(2, 3), -94.8923440, epsilon);
  EXPECT_NEAR(complements(2, 4), -104.2553778, epsilon);
  EXPECT_NEAR(complements(3, 0), -204.3331151, epsilon);
  EXPECT_NEAR(complements(3, 1), 1409.5687387, epsilon);
  EXPECT_NEAR(complements(3, 2), 826.39946933, epsilon);
  EXPECT_NEAR(complements(3, 3), -2099.6555784, epsilon);
  EXPECT_NEAR(complements(3, 4), -109.9985667, epsilon);
  EXPECT_NEAR(complements(4, 0), 379.4267136, epsilon);
  EXPECT_NEAR(complements(4, 1), -2413.1103757, epsilon);
  EXPECT_NEAR(complements(4, 2), -930.3439960, epsilon);
  EXPECT_NEAR(complements(4, 3), 2466.14439562, epsilon);
  EXPECT_NEAR(complements(4, 4), 259.9083586, epsilon);
}

TEST(MatrixTest, MinorSmall) {
  S21Matrix matrix(1, 1);
  EXPECT_THROW(matrix.MinorMatrix(1, 1), std::invalid_argument);
}

TEST(MatrixTest, MinorOutOfRange) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.MinorMatrix(5, 2), std::invalid_argument);
}

TEST(MatrixTest, InverseMatrix) {
  S21Matrix matrix;
  S21Matrix inversed;
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;
  inversed = matrix.InverseMatrix();
  EXPECT_EQ(inversed.GetCols(), 3);
  EXPECT_EQ(inversed.GetRows(), 3);
  EXPECT_EQ(inversed(0, 0), 1);
  EXPECT_EQ(inversed(0, 1), -1);
  EXPECT_EQ(inversed(0, 2), 1);
  EXPECT_EQ(inversed(1, 0), -38);
  EXPECT_EQ(inversed(1, 1), 41);
  EXPECT_EQ(inversed(1, 2), -34);
  EXPECT_EQ(inversed(2, 0), 27);
  EXPECT_EQ(inversed(2, 1), -29);
  EXPECT_EQ(inversed(2, 2), 24);
}

TEST(MatrixTest, DeterminantZero) {
  S21Matrix matrix;
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(MatrixTest, OpPlus) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  S21Matrix result = matrix + other_matrix;
  EXPECT_NEAR(result(0, 0), 5.0, epsilon);
}

TEST(MatrixTest, OpMinus) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  S21Matrix result = matrix - other_matrix;
  EXPECT_NEAR(result(0, 0), 1.0, epsilon);
}

TEST(MatrixTest, OpMul) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  S21Matrix result = matrix * other_matrix;
  EXPECT_NEAR(result(0, 0), 6.0, epsilon);
}

TEST(MatrixTest, OpMulNum) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  double num = 2.0;
  S21Matrix result = matrix * num;
  EXPECT_NEAR(result(0, 0), 6.0, epsilon);
}

TEST(MatrixTest, OpEq) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 3.0;
  EXPECT_EQ(matrix == other_matrix, true);
}

TEST(MatrixTest, OpEqPlus) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  matrix += other_matrix;
  EXPECT_NEAR(matrix(0, 0), 5.0, epsilon);
}

TEST(MatrixTest, OpEqMinus) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  matrix -= other_matrix;
  EXPECT_NEAR(matrix(0, 0), 1.0, epsilon);
}

TEST(MatrixTest, OpEqMul) {
  S21Matrix matrix;
  matrix(0, 0) = 3.0;
  S21Matrix other_matrix;
  other_matrix(0, 0) = 2.0;
  matrix *= other_matrix;
  EXPECT_NEAR(matrix(0, 0), 6.0, epsilon);
}

TEST(MatrixTest, Index) {
  S21Matrix matrix;
  EXPECT_THROW(matrix(5, 3), std::out_of_range);
}