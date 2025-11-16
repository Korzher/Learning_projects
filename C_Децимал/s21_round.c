#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  // Предварительная проверка аргумента
  if (result == NULL) return 1;

  int outcome = 0;
  s21_decimal truncated = {0};
  s21_truncate(value, &truncated);

  s21_decimal diff = {0};
  s21_sub(value, truncated, &diff);
  if (s21_get_sign(diff)) {
    s21_negate(diff, &diff);
  }

  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);

  int need_round_up = s21_is_greater_or_equal(diff, half);

  if (need_round_up) {
    s21_decimal one = {{1, 0, 0, 0}};
    if (s21_get_sign(value)) {
      if (s21_sub(truncated, one, result)) outcome = 1;
    } else {
      if (s21_add(truncated, one, result)) outcome = 1;
    }
  } else {
    *result = truncated;
  }

  if (!outcome) s21_set_scale(result, 0);
  return outcome;
}