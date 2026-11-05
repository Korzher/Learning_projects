#include "s21_decimal.h"

void s21_set_scale(s21_decimal *d, int scale) {
  // Предварительная проверка аргумента
  if (!d) return;

  if (scale > 28) scale = 28;
  d->bits[3] &= ~S21_DECIMAL_SCALE_MASK;
  d->bits[3] |= ((scale << 16) & S21_DECIMAL_SCALE_MASK);
}