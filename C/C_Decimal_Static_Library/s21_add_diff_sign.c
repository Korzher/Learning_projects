#include "s21_decimal.h"

int s21_add_diff_sign(s21_decimal a, s21_decimal b, s21_decimal *result,
                      int scale) {
  int outcome = 0;

  int cmp = s21_compare_abs(a, b);

  if (cmp == 0) {
    memset(result, 0, sizeof(s21_decimal));
    s21_set_scale(result, 0);
    s21_set_sign(result, 0);
  } else {
    s21_decimal *big = (cmp > 0) ? &a : &b;
    s21_decimal *small = (cmp > 0) ? &b : &a;
    int result_sign = s21_get_sign(*big);

    uint64_t borrow = 0;
    for (int i = 0; i < 3; ++i) {
      uint64_t big_val = big->bits[i];
      uint64_t small_val = small->bits[i] + borrow;
      if (big_val < small_val) {
        result->bits[i] = (uint32_t)((1ULL << 32) + big_val - small_val);
        borrow = 1;
      } else {
        result->bits[i] = (uint32_t)(big_val - small_val);
        borrow = 0;
      }
    }
    s21_set_scale(result, scale);
    s21_set_sign(result, result_sign);
  }
  return outcome;
}