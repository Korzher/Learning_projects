#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  // Предварительная проверка аргумента
  if (!result) return 1;

  s21_truncate(value, result);
  if (s21_get_sign(value) && !s21_is_zero(value)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(*result, one, result);
  }
  return 0;
}