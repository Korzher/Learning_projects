#include "s21_decimal.h"

void s21_set_sign(s21_decimal *d, int sign) {
  d->bits[3] &= ~0x80000000;
  if (sign) d->bits[3] |= 0x80000000;
}