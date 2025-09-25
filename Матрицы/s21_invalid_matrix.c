#include "s21_matrix.h"

int s21_invalid_matrix(matrix_t *matrix) {
  int code = OK;
  if (!matrix || matrix->rows <= 0 || matrix->columns <= 0)
    code = INCORRECT_MATRIX;
  return code;
}