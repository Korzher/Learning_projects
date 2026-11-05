#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // Предварительная проверка аргументов
  if (!result || rows <= 0 || columns <= 0) return INCORRECT_MATRIX;

  int code = OK;

  result->rows = 0;
  result->columns = 0;
  result->matrix = (double **)malloc(rows * sizeof(double *));

  if (!result->matrix) {
    code = CALCULATION_ERROR;
  } else {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        code = CALCULATION_ERROR;
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        result->matrix = NULL;
        break;
      }
    }
  }

  if (code == OK) {
    result->rows = rows;
    result->columns = columns;
  }

  return code;
}