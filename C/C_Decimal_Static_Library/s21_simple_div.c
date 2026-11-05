#include "s21_decimal.h"

int s21_simple_div(s21_decimal dividend, s21_decimal divisor,
                   s21_decimal *quotient, s21_decimal *remainder) {
  s21_decimal zero = {0}, quot = {0};
  int outcome = 0;
  if (remainder) *remainder = zero;

  int dividend_hi = s21_highest_bit(dividend);
  int divisor_hi = s21_highest_bit(divisor);

  if (dividend_hi < divisor_hi) {
    if (quotient) *quotient = zero;
    if (remainder) *remainder = dividend;
  } else {
    int shift = dividend_hi - divisor_hi;

    for (int i = 0; i < shift; i++) s21_shift_left(&divisor);

    for (int i = shift; i >= 0; i--) {
      int cmp = s21_compare_bits(dividend, divisor);

      if (cmp >= 0) {
        s21_subtract_raw_bits(&dividend, divisor);
        quot.bits[i / 32] |= (1u << (i % 32));
      }

      s21_shift_right(&divisor);
    }

    if (quotient) *quotient = quot;
    if (remainder) *remainder = dividend;
  }
  return outcome;
}