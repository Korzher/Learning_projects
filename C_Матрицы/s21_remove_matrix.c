#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  // Предварительная проверка аргументов
  if (!A) return;

  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }

  A->rows = 0;
  A->columns = 0;
}
