#include "s21_matrix.h"

int s21_size_comp(matrix_t *A, matrix_t *B) {
  // Предварительная проверка аргументов
  if (!A || !B) return FAILURE;

  int code = SUCCESS;
  if ((A->rows != B->rows) || (A->columns != B->columns)) code = FAILURE;
  return code;
}