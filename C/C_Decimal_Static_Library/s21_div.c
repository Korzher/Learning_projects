#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Предварительные проверки аргумента
  if (s21_is_zero(value_2)) return 3;
  if (s21_is_zero(value_1)) {
    *result = value_1;
    s21_set_sign(result, s21_get_sign(value_1) ^ s21_get_sign(value_2));
    s21_set_scale(result, 0);
    return 0;
  }

  int sign = s21_get_sign(value_1) ^ s21_get_sign(value_2);
  s21_decimal a = value_1, b = value_2;
  s21_normalize_scale(&a, &b);

  s21_decimal quotient = {0}, remainder = {0};
  s21_simple_div(a, b, &quotient, &remainder);

  int result_scale = 0;

  while (!s21_is_zero(remainder) && result_scale < 28) {
    s21_multiply_by_ten_with_add(&remainder, 0);
    s21_decimal digit = {0}, rem = {0};
    s21_simple_div(remainder, b, &digit, &rem);
    s21_multiply_by_ten_with_add(&quotient, digit.bits[0]);
    remainder = rem;
    result_scale++;
  }

  *result = quotient;
  s21_set_sign(result, sign);
  s21_set_scale(result, result_scale);

  return 0;
}