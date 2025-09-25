#include "s21_matrix.h"

int s21_minor_matrix(matrix_t *matrix, int i, int j, matrix_t *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(matrix) || !result || i < 0 || i >= matrix->rows ||
      j < 0 || j >= matrix->columns) {
    return INCORRECT_MATRIX;
  }

  int code = OK;
  if (s21_create_matrix(matrix->rows - 1, matrix->columns - 1, result) != OK) {
    code = CALCULATION_ERROR;
  } else {
    for (int k = 0; k < matrix->rows; k++) {
      if (k == i) continue;
      for (int l = 0; l < matrix->columns; l++) {
        if (l == j) continue;
        result->matrix[k < i ? k : k - 1][l < j ? l : l - 1] =
            matrix->matrix[k][l];
      }
    }
  }
  return code;
}