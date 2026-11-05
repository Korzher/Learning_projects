#define _GNU_SOURCE
#include <check.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "s21_matrix.h"

static bool fail_calloc = false;

void *__wrap_calloc(size_t nmemb, size_t size) {
  static void *(*real_calloc)(size_t, size_t) = NULL;

  if (!real_calloc) {
    real_calloc = dlsym(RTLD_NEXT, "calloc");
  }

  if (fail_calloc) {
    return NULL;
  }

  return real_calloc(nmemb, size);
}

START_TEST(test_s21_create_matrix) {
  // TEST: s21_create_matrix корректно создает матрицу
  int rows = 3;
  int columns = 2;
  matrix_t result;
  int code = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_alloc_failure) {
  // TEST: s21_create_matrix корректно обрабатывает ошибку выделения памяти
  int rows = 3;
  int columns = 2;
  matrix_t result;

  fail_calloc = true;

  int code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);
  ck_assert_ptr_null(result.matrix);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);

  fail_calloc = false;
}
END_TEST

START_TEST(test_s21_eq_matrix_equal) {
  // TEST: s21_eq_matrix корректно сравнивает матрицы
  matrix_t value_1;
  matrix_t value_2;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;
  int code = s21_eq_matrix(&value_1, &value_2);

  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_eq_matrix_not_equal) {
  // TEST: s21_eq_matrix корректно сравнивает неравные матрицы
  matrix_t value_1;
  matrix_t value_2;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 2;
  value_2.matrix[0][1] = 1;
  int code = s21_eq_matrix(&value_1, &value_2);

  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_eq_matrix_not_equal_size) {
  // TEST: s21_eq_matrix корректно сравнивает матрицы разного размера
  matrix_t value_1;
  matrix_t value_2;
  int rows_1 = 2, rows_2 = 3;
  int columns = 2;
  s21_create_matrix(rows_1, columns, &value_1);
  s21_create_matrix(rows_2, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 2;
  value_2.matrix[0][1] = 1;
  int code = s21_eq_matrix(&value_1, &value_2);

  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_eq_matrix_incorrect_matrix) {
  // TEST: s21_eq_matrix корректно проверяет матрицы на валидность
  matrix_t value_1;
  matrix_t value_2;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.rows = 0;
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;
  int code = s21_eq_matrix(&value_1, &value_2);
  value_1.rows = 2;

  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_sum_matrix_correct_matrix) {
  // TEST: s21_sum_matrix корректно складывает матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;
  int code = s21_sum_matrix(&value_1, &value_2, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_int_eq(result.matrix[0][0], 2);
  ck_assert_int_eq(result.matrix[0][1], 4);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sum_matrix_incorrect_matrix) {
  // TEST: s21_sum_matrix корректно роняет неправильные матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.rows = 0;
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;
  int code = s21_sum_matrix(&value_1, &value_2, &result);
  value_1.rows = 2;

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_sum_matrix_memory_alloc_error) {
  // TEST: s21_sum_matrix обрабатывает ошибку выделения памяти
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;

  fail_calloc = true;
  int code = s21_sum_matrix(&value_1, &value_2, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_sub_matrix_correct_matrix) {
  // TEST: s21_sub_matrix корректно вычитает матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 2;
  value_2.matrix[0][1] = 1;
  int code = s21_sub_matrix(&value_1, &value_2, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_int_eq(result.matrix[0][0], 2);
  ck_assert_int_eq(result.matrix[0][1], 1);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sub_matrix_incorrect_matrix) {
  // TEST: s21_sub_matrix корректно роняет неправильные матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.rows = 0;
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 2;
  value_2.matrix[0][1] = 1;
  int code = s21_sub_matrix(&value_1, &value_2, &result);
  value_1.rows = 2;

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_sub_matrix_memory_alloc_error) {
  // TEST: s21_sub_matrix обрабатывает ошибку выделения памяти
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;

  fail_calloc = true;
  int code = s21_sub_matrix(&value_1, &value_2, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_mult_matrix_correct_matrix) {
  // TEST: s21_mult_matrix корректно перемножает квадратные матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_1.matrix[0][2] = 1;
  value_1.matrix[1][0] = 3;
  value_1.matrix[1][1] = 2;
  value_1.matrix[1][2] = 3;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = 2;
  value_1.matrix[2][2] = 6;

  value_2.matrix[0][0] = 4;
  value_2.matrix[0][1] = 5;
  value_2.matrix[0][2] = 3;
  value_2.matrix[1][0] = 1;
  value_2.matrix[1][1] = 8;
  value_2.matrix[1][2] = 2;
  value_2.matrix[2][0] = 11;
  value_2.matrix[2][1] = 2;
  value_2.matrix[2][2] = 3;
  int code = s21_mult_matrix(&value_1, &value_2, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(result.matrix[0][0], 29);
  ck_assert_int_eq(result.matrix[0][1], 38);
  ck_assert_int_eq(result.matrix[0][2], 19);
  ck_assert_int_eq(result.matrix[1][0], 47);
  ck_assert_int_eq(result.matrix[1][1], 37);
  ck_assert_int_eq(result.matrix[1][2], 22);
  ck_assert_int_eq(result.matrix[2][0], 88);
  ck_assert_int_eq(result.matrix[2][1], 53);
  ck_assert_int_eq(result.matrix[2][2], 37);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_matrix_correct_matrix_diff_size) {
  // TEST: s21_mult_matrix корректно перемножает матрицы разного размера
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows_1 = 3, rows_2 = 2;
  int columns_1 = 2, columns_2 = 4;
  s21_create_matrix(rows_1, columns_1, &value_1);
  s21_create_matrix(rows_2, columns_2, &value_2);
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_1.matrix[1][0] = 3;
  value_1.matrix[1][1] = 2;
  value_1.matrix[2][0] = 4;
  value_1.matrix[2][1] = 1;

  value_2.matrix[0][0] = 4;
  value_2.matrix[0][1] = 5;
  value_2.matrix[0][2] = 3;
  value_2.matrix[0][3] = 2;
  value_2.matrix[1][0] = 1;
  value_2.matrix[1][1] = 8;
  value_2.matrix[1][2] = 2;
  value_2.matrix[1][3] = 6;

  int code = s21_mult_matrix(&value_1, &value_2, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 4);
  ck_assert_int_eq(result.matrix[0][0], 18);
  ck_assert_int_eq(result.matrix[0][1], 36);
  ck_assert_int_eq(result.matrix[0][2], 16);
  ck_assert_int_eq(result.matrix[0][3], 20);
  ck_assert_int_eq(result.matrix[1][0], 14);
  ck_assert_int_eq(result.matrix[1][1], 31);
  ck_assert_int_eq(result.matrix[1][2], 13);
  ck_assert_int_eq(result.matrix[1][3], 18);
  ck_assert_int_eq(result.matrix[2][0], 17);
  ck_assert_int_eq(result.matrix[2][1], 28);
  ck_assert_int_eq(result.matrix[2][2], 14);
  ck_assert_int_eq(result.matrix[2][3], 14);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_matrix_correct_matrix_float) {
  // TEST: s21_mult_matrix корректно перемножает матрицы разного размера с типом
  // float
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows_1 = 3, rows_2 = 2;
  int columns_1 = 2, columns_2 = 4;
  s21_create_matrix(rows_1, columns_1, &value_1);
  s21_create_matrix(rows_2, columns_2, &value_2);
  value_1.matrix[0][0] = 4.563543f;
  value_1.matrix[0][1] = 2.762374f;
  value_1.matrix[1][0] = 3.263483f;
  value_1.matrix[1][1] = 2.187246f;
  value_1.matrix[2][0] = 4.987234f;
  value_1.matrix[2][1] = 1.829342f;

  value_2.matrix[0][0] = 4.823498;
  value_2.matrix[0][1] = 5.482735;
  value_2.matrix[0][2] = 3.283644;
  value_2.matrix[0][3] = 2.283650;
  value_2.matrix[1][0] = 1.91745;
  value_2.matrix[1][1] = 8.583405;
  value_2.matrix[1][2] = 2.183654;
  value_2.matrix[1][3] = 6.863454;

  int code = s21_mult_matrix(&value_1, &value_2, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 4);
  ck_assert_double_eq_tol(result.matrix[0][0], 27.308954, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][1], 48.731271, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][2], 21.017119, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][3], 29.380961, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][0], 19.935338, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][1], 36.666830, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][2], 15.492304, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][3], 22.464715, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][0], 27.563585, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][1], 43.045665, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][2], 20.370950, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][3], 23.944701, 1e-5);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_matrix_incorrect_matrix) {
  // TEST: s21_sub_matrix корректно роняет неправильные матрицы
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.rows = 0;
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 2;
  value_2.matrix[0][1] = 1;
  int code = s21_mult_matrix(&value_1, &value_2, &result);
  value_1.rows = 2;

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_mult_matrix_memory_alloc_error) {
  // TEST: s21_sum_matrix обрабатывает ошибку выделения памяти
  matrix_t value_1;
  matrix_t value_2;
  matrix_t result;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  s21_create_matrix(rows, columns, &value_2);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_2.matrix[0][0] = 1;
  value_2.matrix[0][1] = 2;

  fail_calloc = true;
  int code = s21_mult_matrix(&value_1, &value_2, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&value_2);
}

START_TEST(test_s21_mult_number_matrix_correct_matrix) {
  // TEST: s21_mult_matrix корректно перемножает квадратную матрицу на число
  matrix_t value_1;
  matrix_t result;
  double mult = 1.65342;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_1.matrix[0][2] = 1;
  value_1.matrix[1][0] = 3;
  value_1.matrix[1][1] = 2;
  value_1.matrix[1][2] = 3;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = 2;
  value_1.matrix[2][2] = 5;
  int code = s21_mult_number(&value_1, mult, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq_tol(result.matrix[0][0], 6.61368, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.30684, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][2], 1.65342, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.96026, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][1], 3.30684, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][2], 4.96026, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][0], 8.2671, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][1], 3.30684, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][2], 8.2671, 1e-5);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_matrix_rectangle) {
  // TEST: s21_mult_number корректно перемножает прямоугольную матрицу на число
  matrix_t value_1;
  matrix_t result;
  double mult = 7.12734;
  int rows = 3;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1.27363f;
  value_1.matrix[0][1] = 2.34522f;
  value_1.matrix[1][0] = 9.39724f;
  value_1.matrix[1][1] = 1.39748f;
  value_1.matrix[2][0] = 4.82745f;
  value_1.matrix[2][1] = 1.29056f;
  int code = s21_mult_number(&value_1, mult, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 9.07759, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][1], 16.71518, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][0], 66.97732, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][1], 9.960315, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][0], 34.406877, 1e-5);
  ck_assert_double_eq_tol(result.matrix[2][1], 9.198259, 1e-5);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_matrix_incorrect_matrix) {
  // TEST: s21_sub_number_matrix корректно роняет неправильные матрицы
  matrix_t value_1;
  matrix_t result;
  double mult = 7.12734;
  int rows = 3;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  value_1.rows = 0;
  value_1.columns = 0;
  int code = s21_mult_number(&value_1, mult, &result);
  value_1.rows = 3;
  value_1.columns = 2;
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_mult_number_matrix_memory_alloc_error) {
  // TEST: s21_mult_number обрабатывает ошибку выделения памяти
  matrix_t value_1;
  matrix_t result;
  double mult = 7.12734;
  int rows = 3;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1.27363f;
  value_1.matrix[0][1] = 2.34522f;
  value_1.matrix[1][0] = 9.39724f;
  value_1.matrix[1][1] = 1.39748f;
  value_1.matrix[2][0] = 4.82745f;
  value_1.matrix[2][1] = 1.29056f;

  fail_calloc = true;
  int code = s21_mult_number(&value_1, mult, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_transpose) {
  // TEST: s21_transpose правильно транспонирует матрицы
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 4;
  value_1.matrix[0][1] = 2;
  value_1.matrix[1][0] = 9;
  value_1.matrix[1][1] = 3;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = 7;

  int code = s21_transpose(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(result.matrix[0][0], 4);
  ck_assert_int_eq(result.matrix[0][1], 9);
  ck_assert_int_eq(result.matrix[0][2], 5);
  ck_assert_int_eq(result.matrix[1][0], 2);
  ck_assert_int_eq(result.matrix[1][1], 3);
  ck_assert_int_eq(result.matrix[1][2], 7);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_minor_matrix_error) {
  // TEST: s21_minor_matrix корректно обрабатывает ошибку в матрице
  matrix_t result;
  int code = s21_minor_matrix(NULL, 0, 0, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

START_TEST(test_s21_calc_complements) {
  // TEST: s21_calc_complements верно считает матрицу дополнений
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_1.matrix[0][2] = 3;
  value_1.matrix[1][0] = 0;
  value_1.matrix[1][1] = 4;
  value_1.matrix[1][2] = 2;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = 2;
  value_1.matrix[2][2] = 1;

  int code = s21_calc_complements(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(result.matrix[0][0], 0);
  ck_assert_int_eq(result.matrix[0][1], 10);
  ck_assert_int_eq(result.matrix[0][2], -20);
  ck_assert_int_eq(result.matrix[1][0], 4);
  ck_assert_int_eq(result.matrix[1][1], -14);
  ck_assert_int_eq(result.matrix[1][2], 8);
  ck_assert_int_eq(result.matrix[2][0], -8);
  ck_assert_int_eq(result.matrix[2][1], -2);
  ck_assert_int_eq(result.matrix[2][2], 4);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_complements_rectangle) {
  // TEST: s21_calc_complements отбрасывает прямоугольные матрицы
  matrix_t value_1;
  matrix_t result;
  int rows = 2;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);

  int code = s21_calc_complements(&value_1, &result);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_calc_complements_1x1) {
  // TEST: s21_calc_complements верно считает матрицу размером 1х1
  matrix_t value_1;
  matrix_t result;
  int rows = 1;
  int columns = 1;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1;

  int code = s21_calc_complements(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_int_eq(result.matrix[0][0], 1);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_complements_error) {
  // TEST: s21_calc_complements верно считает матрицу дополнений
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_1.matrix[0][2] = 3;
  value_1.matrix[1][0] = 0;
  value_1.matrix[1][1] = 4;
  value_1.matrix[1][2] = 2;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = 2;
  value_1.matrix[2][2] = 1;

  fail_calloc = true;
  int code = s21_calc_complements(&value_1, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_calc_complements_1x1_error) {
  // TEST: s21_calc_complements верно считает матрицу размером 1х1
  matrix_t value_1;
  matrix_t result;
  int rows = 1;
  int columns = 1;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1;

  fail_calloc = true;
  int code = s21_calc_complements(&value_1, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant) {
  // TEST: s21_determinant верно находит ненулевой определитель
  matrix_t value_1;
  double result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 2;
  value_1.matrix[0][1] = 5;
  value_1.matrix[0][2] = 7;
  value_1.matrix[1][0] = 6;
  value_1.matrix[1][1] = 3;
  value_1.matrix[1][2] = 4;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = -2;
  value_1.matrix[2][2] = -3;

  int code = s21_determinant(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -1, 1e-5);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant_5x5) {
  // TEST: s21_determinant верно находит ненулевой определитель в большой матрице
  matrix_t value_1;
  double result;
  int rows = 5;
  int columns = 5;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 7.23455;
  value_1.matrix[0][1] = 2.34562;
  value_1.matrix[0][2] = 4.35263;
  value_1.matrix[0][3] = 2.34623;
  value_1.matrix[0][4] = 4.53452;
  value_1.matrix[1][0] = 3.62365;
  value_1.matrix[1][1] = 2.35846;
  value_1.matrix[1][2] = 1.25651;
  value_1.matrix[1][3] = 1.23196;
  value_1.matrix[1][4] = 9.41528;
  value_1.matrix[2][0] = 1.48255;
  value_1.matrix[2][1] = 1.45923;
  value_1.matrix[2][2] = 9.97854;
  value_1.matrix[2][3] = 4.56378;
  value_1.matrix[2][4] = 3.79864;
  value_1.matrix[3][0] = 6.76854;
  value_1.matrix[3][1] = 7.86945;
  value_1.matrix[3][2] = 7.98645;
  value_1.matrix[3][3] = 8.96722;
  value_1.matrix[3][4] = 6.68456;
  value_1.matrix[4][0] = 5.56645;
  value_1.matrix[4][1] = 6.98697;
  value_1.matrix[4][2] = 6.78695;
  value_1.matrix[4][3] = 6.42368;
  value_1.matrix[4][4] = 7.56756;

  int code = s21_determinant(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, -3253.87362, 1e-5);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant_1x1) {
  // TEST: s21_determinant верно находит ненулевой определитель
  matrix_t value_1;
  double result;
  int rows = 1;
  int columns = 1;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 2;

  int code = s21_determinant(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 2, 1e-5);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant_not_rectangle) {
  // TEST: s21_determinant верно оибрасывает неквадратные матрицы
  matrix_t value_1;
  double result;
  int rows = 2;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);

  int code = s21_determinant(&value_1, &result);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant_memory_error) {
  // TEST: s21_determinant обрабатывает ошибку выделения памяти
  matrix_t value_1;
  double result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 2;
  value_1.matrix[0][1] = 5;
  value_1.matrix[0][2] = 7;
  value_1.matrix[1][0] = 6;
  value_1.matrix[1][1] = 3;
  value_1.matrix[1][2] = 4;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = -2;
  value_1.matrix[2][2] = -3;

  fail_calloc = true;
  int code = s21_determinant(&value_1, &result);
  fail_calloc = true;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_determinant_zero) {
  // TEST: s21_determinant верно находит нулевой определитель
  matrix_t value_1;
  double result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 1;
  value_1.matrix[0][1] = 2;
  value_1.matrix[0][2] = 3;
  value_1.matrix[1][0] = 4;
  value_1.matrix[1][1] = 5;
  value_1.matrix[1][2] = 6;
  value_1.matrix[2][0] = 7;
  value_1.matrix[2][1] = 8;
  value_1.matrix[2][2] = 9;

  int code = s21_determinant(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result, 0, 1e-5);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_inverse_matrix) {
  // TEST: s21_inverse_matrix корректно обрабатывает обычную матрицу
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 2;
  value_1.matrix[0][1] = 5;
  value_1.matrix[0][2] = 7;
  value_1.matrix[1][0] = 6;
  value_1.matrix[1][1] = 3;
  value_1.matrix[1][2] = 4;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = -2;
  value_1.matrix[2][2] = -3;

  int code = s21_inverse_matrix(&value_1, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(result.matrix[0][0], 1);
  ck_assert_int_eq(result.matrix[0][1], -1);
  ck_assert_int_eq(result.matrix[0][2], 1);
  ck_assert_int_eq(result.matrix[1][0], -38);
  ck_assert_int_eq(result.matrix[1][1], 41);
  ck_assert_int_eq(result.matrix[1][2], -34);
  ck_assert_int_eq(result.matrix[2][0], 27);
  ck_assert_int_eq(result.matrix[2][1], -29);
  ck_assert_int_eq(result.matrix[2][2], 24);
  s21_remove_matrix(&value_1);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_inverse_matrix_not_rectangle) {
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 2;
  s21_create_matrix(rows, columns, &value_1);
  
  value_1.matrix[0][0] = 2;
  value_1.matrix[0][1] = 5;
  value_1.matrix[1][0] = 6;
  value_1.matrix[1][1] = 3;
  value_1.matrix[2][0] = 7;
  value_1.matrix[2][1] = 4;

  int code = s21_inverse_matrix(&value_1, &result);

  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&value_1);
}

START_TEST(test_s21_inverse_matrix_memory_error) {
  // TEST: s21_inverse_matrix корректно обрабатывает ошибку выделения памяти
  matrix_t value_1;
  matrix_t result;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &value_1);
  value_1.matrix[0][0] = 2;
  value_1.matrix[0][1] = 5;
  value_1.matrix[0][2] = 7;
  value_1.matrix[1][0] = 6;
  value_1.matrix[1][1] = 3;
  value_1.matrix[1][2] = 4;
  value_1.matrix[2][0] = 5;
  value_1.matrix[2][1] = -2;
  value_1.matrix[2][2] = -3;

  fail_calloc = true;
  int code = s21_inverse_matrix(&value_1, &result);
  fail_calloc = false;

  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&value_1);
}

SRunner *create_runner() {
  SRunner *sr;
  Suite *s21_create_matrix;
  Suite *s21_eq_matrix;
  Suite *s21_arithmetic;
  Suite *s21_transform;
  TCase *tc_s21_create_matrix;
  TCase *tc_s21_eq_matrix;
  TCase *tc_s21_sum;
  TCase *tc_s21_sub;
  TCase *tc_s21_mult;
  TCase *tc_s21_mult_number;
  TCase *tc_s21_transpose;
  TCase *tc_s21_minor_matrix;
  TCase *tc_s21_calc_complements;
  TCase *tc_s21_determinant;
  TCase *tc_s21_inverse_matrix;

  s21_create_matrix = suite_create("create_matrix");
  s21_eq_matrix = suite_create("eq_matrix");
  s21_arithmetic = suite_create("arithmetic");
  s21_transform = suite_create("transform");

  sr = srunner_create(s21_create_matrix);
  srunner_add_suite(sr, s21_eq_matrix);
  srunner_add_suite(sr, s21_arithmetic);
  srunner_add_suite(sr, s21_transform);

  tc_s21_create_matrix = tcase_create("tc_create_matrix");
  tcase_add_test(tc_s21_create_matrix, test_s21_create_matrix);
  tcase_add_test(tc_s21_create_matrix, test_s21_create_matrix_alloc_failure);

  tc_s21_eq_matrix = tcase_create("tc_eq_matrix");
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix_equal);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix_not_equal);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix_not_equal_size);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix_incorrect_matrix);

  tc_s21_sum = tcase_create("sum");
  tcase_add_test(tc_s21_sum, test_s21_sum_matrix_correct_matrix);
  tcase_add_test(tc_s21_sum, test_s21_sum_matrix_incorrect_matrix);
  tcase_add_test(tc_s21_sum, test_s21_sum_matrix_memory_alloc_error);

  tc_s21_sub = tcase_create("sub");
  tcase_add_test(tc_s21_sub, test_s21_sub_matrix_correct_matrix);
  tcase_add_test(tc_s21_sub, test_s21_sub_matrix_incorrect_matrix);
  tcase_add_test(tc_s21_sub, test_s21_sub_matrix_memory_alloc_error);

  tc_s21_mult = tcase_create("mult");
  tcase_add_test(tc_s21_mult, test_s21_mult_matrix_correct_matrix);
  tcase_add_test(tc_s21_mult, test_s21_mult_matrix_correct_matrix_diff_size);
  tcase_add_test(tc_s21_mult, test_s21_mult_matrix_incorrect_matrix);
  tcase_add_test(tc_s21_mult, test_s21_mult_matrix_memory_alloc_error);
  tcase_add_test(tc_s21_mult, test_s21_mult_matrix_correct_matrix_float);

  tc_s21_mult_number = tcase_create("mult_number");
  tcase_add_test(tc_s21_mult_number,
                 test_s21_mult_number_matrix_correct_matrix);
  tcase_add_test(tc_s21_mult_number, test_s21_mult_number_matrix_rectangle);
  tcase_add_test(tc_s21_mult_number,
                 test_s21_mult_number_matrix_incorrect_matrix);
  tcase_add_test(tc_s21_mult_number,
                 test_s21_mult_number_matrix_memory_alloc_error);

  tc_s21_transpose = tcase_create("transpose");
  tcase_add_test(tc_s21_transpose, test_s21_transpose);

  tc_s21_minor_matrix = tcase_create("minor_matrix");
  tcase_add_test(tc_s21_minor_matrix, test_s21_minor_matrix_error);

  tc_s21_calc_complements = tcase_create("calc_complements");
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements_rectangle);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements_1x1);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements_error);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements_1x1_error);

  tc_s21_determinant = tcase_create("determinant");
  tcase_add_test(tc_s21_determinant, test_s21_determinant);
  tcase_add_test(tc_s21_determinant, test_s21_determinant_not_rectangle);
  tcase_add_test(tc_s21_determinant, test_s21_determinant_memory_error);
  tcase_add_test(tc_s21_determinant, test_s21_determinant_1x1);
  tcase_add_test(tc_s21_determinant,test_s21_determinant_5x5);
  tcase_add_test(tc_s21_determinant, test_s21_determinant_zero);

  tc_s21_inverse_matrix = tcase_create("inverse");
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix);
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix_not_rectangle);
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix_memory_error);

  suite_add_tcase(s21_create_matrix, tc_s21_create_matrix);
  suite_add_tcase(s21_eq_matrix, tc_s21_eq_matrix);
  suite_add_tcase(s21_arithmetic, tc_s21_sum);
  suite_add_tcase(s21_arithmetic, tc_s21_sub);
  suite_add_tcase(s21_arithmetic, tc_s21_mult);
  suite_add_tcase(s21_arithmetic, tc_s21_mult_number);
  suite_add_tcase(s21_transform, tc_s21_transpose);
  suite_add_tcase(s21_transform, tc_s21_minor_matrix);
  suite_add_tcase(s21_transform, tc_s21_calc_complements);
  suite_add_tcase(s21_transform, tc_s21_determinant);
  suite_add_tcase(s21_transform, tc_s21_inverse_matrix);

  return sr;
}

int main() {
  SRunner *sr = create_runner();
  srunner_run_all(sr, CK_NORMAL);
  int failed_quantity = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_quantity == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}