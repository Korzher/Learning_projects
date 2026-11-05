#include "s21_decimal.h"

void s21_shift_left(s21_decimal *dec) {
  uint32_t carry = 0;
  for (int j = 0; j < 3; j++) {
    uint64_t v = ((uint64_t)dec->bits[j]) << 1 | carry;
    dec->bits[j] = (uint32_t)(v & 0xFFFFFFFF);
    carry = (v >> 32) & 1;
  }
}