#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A)) return INCORRECT_MATRIX;

  int code = s21_create_matrix(A->columns, A->rows, result);

  if (code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  if (code != OK && result->matrix) s21_remove_matrix(result);
  return code;
}