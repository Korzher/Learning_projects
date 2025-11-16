#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Предварительная проверка аргументов
  if (s21_invalid_matrix(A) || s21_invalid_matrix(B)) {
    return FAILURE;
  }

  int code = SUCCESS;
  if (!s21_size_comp(A, B)) {
    code = FAILURE;
  } else {
    int rows = A->rows;
    int columns = A->columns;

    for (int i = 0; i < rows && code == SUCCESS; i++) {
      for (int j = 0; j < columns && code == SUCCESS; j++) {
        if (s21_fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          code = FAILURE;
        }
      }
    }
  }

  return code;
}
