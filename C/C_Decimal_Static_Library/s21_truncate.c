#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int outcome = 0;
  if (!result) {
    outcome = 1;
  } else {
    int scale = s21_get_scale(value);
    for (int i = 0; i < scale; i++) {
      s21_decimal quotient;
      int rem;
      s21_divide_by_ten(&value, &quotient, &rem);
      value = quotient;
    }

    *result = value;
    s21_set_scale(result, 0);
    s21_set_sign(result, s21_get_sign(value));
  }
  return outcome;
}