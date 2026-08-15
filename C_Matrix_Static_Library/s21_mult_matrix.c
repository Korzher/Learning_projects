#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A) || s21_invalid_matrix(B)) {
    return INCORRECT_MATRIX;
  }

  int code = OK;
  if (A->columns != B->rows ||
      (s21_create_matrix(A->rows, B->columns, result) != OK)) {
    code = CALCULATION_ERROR;
  } else {
    int rows = result->rows;
    int columns = result->columns;

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return code;
}
