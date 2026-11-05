#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A) || !result) {
    return INCORRECT_MATRIX;
  }

  int code = OK;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    code = CALCULATION_ERROR;
  } else {
    int rows = A->rows;
    int columns = A->columns;

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return code;
}
