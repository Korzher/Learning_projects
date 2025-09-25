#include "s21_decimal.h"

void s21_subtract_raw_bits(s21_decimal *a, s21_decimal b) {
  uint64_t borrow = 0;
  for (int j = 0; j < 3; j++) {
    uint64_t subtracted = (uint64_t)b.bits[j] + borrow;
    borrow = (a->bits[j] < subtracted) ? 1 : 0;
    a->bits[j] = (uint32_t)(a->bits[j] - subtracted);
  }
}