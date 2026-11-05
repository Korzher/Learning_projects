#include "s21_decimal.h"

void s21_shift_right(s21_decimal *dec) {
  uint32_t carry = 0;
  for (int j = 2; j >= 0; j--) {
    uint64_t v = ((uint64_t)dec->bits[j] | ((uint64_t)carry << 32));
    carry = dec->bits[j] & 1;
    dec->bits[j] = (uint32_t)(v >> 1);
  }
}