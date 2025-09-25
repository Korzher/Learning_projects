#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A) || !result || A->rows != A->columns)
    return INCORRECT_MATRIX;

  int code = OK;
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) == OK) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      code = CALCULATION_ERROR;
    }
  } else if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < A->columns && code == OK; j++) {
        matrix_t minor;
        if (s21_minor_matrix(A, i, j, &minor) == OK) {
          double det = 0.0;
          if (s21_determinant(&minor, &det) == OK) {
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            result->matrix[i][j] = sign * det;
          } else {
            code = CALCULATION_ERROR;
          }
          s21_remove_matrix(&minor);
        } else {
          code = CALCULATION_ERROR;
        }
      }
    }
  } else {
    code = CALCULATION_ERROR;
  }
  if (code != OK && result->matrix) s21_remove_matrix(result);
  return code;
}
