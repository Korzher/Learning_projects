#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  // Предварительная проверка аргумента
  if (!dst) return 1;

  memset(dst, 0, sizeof(s21_decimal));
  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  s21_set_scale(dst, 0);
  return 0;
}