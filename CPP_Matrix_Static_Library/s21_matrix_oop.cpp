#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) {
  try {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  } catch (const std::bad_alloc& e) {
    CleanUp();
    throw;
  }
}

void S21Matrix::CleanUp() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

S21Matrix S21Matrix::MinorMatrix(int row, int col) const {
  if (rows_ <= 1 || cols_ <= 1) {
    throw std::invalid_argument("Matrix is too small");
  }
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::invalid_argument("Index out of range");
  }
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    if (i == row) {
      continue;
    }
    for (int j = 0; j < cols_; j++) {
      if (j == col) {
        continue;
      }
      result.matrix_[i < row ? i : i - 1][j < col ? j : j - 1] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Number of rows or columns must be positive");
  }
  try {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  } catch (const std::bad_alloc& e) {
    CleanUp();
    throw;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  try {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } catch (const std::bad_alloc& e) {
    CleanUp();
    throw;
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { CleanUp(); }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0)
    throw std::invalid_argument("Number of rows must be positive");

  if (new_rows == rows_) return;

  double** new_matrix = new double*[new_rows];
  int min_rows = (new_rows < rows_) ? new_rows : rows_;

  for (int i = 0; i < min_rows; ++i) {
    new_matrix[i] = matrix_[i];
  }
  for (int i = min_rows; i < new_rows; ++i) {
    new_matrix[i] = new double[cols_]();
  }

  if (new_rows < rows_) {
    for (int i = new_rows; i < rows_; ++i) delete[] matrix_[i];
  }

  delete[] matrix_;
  matrix_ = new_matrix;
  rows_ = new_rows;
}

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0)
    throw std::invalid_argument("Number of columns must be positive");

  if (new_cols == cols_) return;

  for (int i = 0; i < rows_; ++i) {
    double* new_row = new double[new_cols]();

    int min_cols = (new_cols < cols_) ? new_cols : cols_;
    for (int j = 0; j < min_cols; ++j) new_row[j] = matrix_[i][j];

    delete[] matrix_[i];
    matrix_[i] = new_row;
  }

  cols_ = new_cols;
}

int S21Matrix::GetCols() const { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > epsilon) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different sizes");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different sizes");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Matrices sizes are not compatible");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  double det = 0.0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = MinorMatrix(0, j);
      det += matrix_[0][j] * minor.Determinant() * ((j % 2 == 0) ? 1.0 : -1.0);
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0;
    return result;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = MinorMatrix(i, j);

      double minor_det = minor.Determinant();

      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;

      result.matrix_[i][j] = sign * minor_det;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (std::fabs(det) < epsilon) {
    throw std::invalid_argument("Determinant is zero");
  }

  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  transposed.MulNumber(1.0 / det);
  return transposed;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& matrix) const {
  return EqMatrix(matrix);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix temp(other);
    Swap(temp);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    CleanUp();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
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

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("Index out of range");
  return matrix_[i][j];
}

void S21Matrix::Swap(S21Matrix& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}