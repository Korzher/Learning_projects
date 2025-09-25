#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int outcome = 0;
  memset(result, 0, sizeof(s21_decimal));

  s21_decimal a = value_1, b = value_2;
  s21_normalize_scale(&a, &b);
  int scale = s21_get_scale(a);

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  if (sign_a == sign_b) {
    outcome = s21_add_same_sign(a, b, result, scale, sign_a);
  } else {
    outcome = s21_add_diff_sign(a, b, result, scale);
  }
  return outcome;
}