#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  // Предварительная проверка аргумента
  if (!dst) return 1;

  double value = 0.0;
  double pow10 = 1.0;
  for (int i = 0; i < 3; i++) {
    value += (double)((uint32_t)src.bits[i]) * pow10;
    pow10 *= 4294967296.0;
  }
  for (int i = 0; i < s21_get_scale(src); i++) value /= 10.0;
  if (s21_get_sign(src)) value = -value;
  *dst = (float)value;
  return 0;
}