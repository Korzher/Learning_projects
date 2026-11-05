#ifndef __S21MATRIXOOP_H__
#define __S21MATRIXOOP_H__

#include <new>
#include <stdexcept>
#include <cmath>

#define epsilon 1e-7

class S21Matrix {
    private:
    int rows_, cols_;
    double **matrix_;

    void CleanUp();

    public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int GetRows(void) const;
    int GetCols(void) const;
    void SetRows(int rows);
    void SetCols(int cols);

    S21Matrix operator+(const S21Matrix& other) const;
    S21Matrix operator-(const S21Matrix& other) const;
    S21Matrix operator*(const S21Matrix& other) const;
    S21Matrix operator*(double num) const;
    bool operator==(const S21Matrix& other) const;
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other) noexcept;
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    double& operator()(int i, int j);


    bool EqMatrix(const S21Matrix& other) const;
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose() const;
    S21Matrix CalcComplements() const;
    double Determinant() const;
    S21Matrix InverseMatrix() const;

    void Swap(S21Matrix& other) noexcept;
    S21Matrix MinorMatrix(int row, int col) const;
};

#endif