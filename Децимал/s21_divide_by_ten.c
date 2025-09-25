#include "s21_decimal.h"

int s21_divide_by_ten(s21_decimal *dividend, s21_decimal *quotient,
                      int *remainder) {
  uint64_t rem = 0;
  memset(quotient, 0, sizeof(s21_decimal));

  for (int i = 2; i >= 0; i--) {
    uint64_t full = ((uint64_t)dividend->bits[i]) + (rem << 32);
    quotient->bits[i] = full / 10;
    rem = full % 10;
  }
  *remainder = rem;

  s21_set_scale(quotient, s21_get_scale(*dividend) - 1);
  s21_set_sign(quotient, s21_get_sign(*dividend));

  return 0;
}