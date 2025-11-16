#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (s21_invalid_matrix(A) || A->rows != A->columns || !result) {
        return INCORRECT_MATRIX;
    }
    int code = OK;
    matrix_t complements = {0}, transposed = {0};
    double det = 0.0;

    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;

    code = s21_determinant(A, &det);
    if (code == OK && s21_fabs(det) <= 1e-6) {
        code = CALCULATION_ERROR;
    }
    if (code == OK) {
        code = s21_calc_complements(A, &complements);
    }
    if (code == OK) {
        code = s21_transpose(&complements, &transposed);
    }
    if (code == OK) {
        code = s21_mult_number(&transposed, 1.0 / det, result);
        if (code != OK && result->matrix) {
            s21_remove_matrix(result);
        }
    }

    if (complements.matrix) s21_remove_matrix(&complements);
    if (transposed.matrix) s21_remove_matrix(&transposed);
    
    return code;
}
