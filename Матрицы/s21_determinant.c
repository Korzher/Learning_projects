#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A) || A->rows != A->columns || !result) {
    return INCORRECT_MATRIX;
  }

  int code = OK;
  *result = 0.0;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor;
      if (s21_minor_matrix(A, 0, i, &minor) != OK) {
        code = CALCULATION_ERROR;
        break;
      }
      double minor_det;
      if (s21_determinant(&minor, &minor_det) != OK) {
        s21_remove_matrix(&minor);
        code = CALCULATION_ERROR;
        break;
      }
      if (i % 2 == 0) {
        *result += A->matrix[0][i] * minor_det;
      } else {
        *result -= A->matrix[0][i] * minor_det;
      }
      s21_remove_matrix(&minor);
    }
  }
  return code;
}
