#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

//Обработка матриц
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

//Сравнение матриц
#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//Хелперы
int s21_size_comp(matrix_t *A, matrix_t *B);
int s21_invalid_matrix(matrix_t *matrix);
int s21_minor_matrix(matrix_t *matrix, int i, int j, matrix_t *result);
double s21_fabs(double x);

#endif