#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || isnan(src) || isinf(src)) return 1;

  int outcome = 0;
  memset(dst, 0, sizeof(s21_decimal));
  int sign = src < 0;
  long double value = fabsl(src);
  if (value >= 1e-28) {
    int scale = 0;
    long double scaled_value = value;
    while (scale < 28 && scaled_value < 1e6 &&
           fabsl(scaled_value - s21_roundl(scaled_value)) > 1e-7) {
      scaled_value *= 10;
      scale++;
    }
    scaled_value = s21_roundl(scaled_value);
    if (scaled_value < 0.0L || scaled_value > 79228162514264337593543950335.0L) {
    outcome = 1;
    } else {
      int digits = 0;
      long double temp = scaled_value;
      while (temp >= 1) {
        digits++;
        temp /= 10;
      }
      if (digits <= 7) {
        while (scale > 0 && s21_fmodl(scaled_value, 10) == 0) {
          scaled_value /= 10;
          scale--;
        }
      }
      uint64_t int_value = (uint64_t)scaled_value;
      dst->bits[0] = int_value & 0xFFFFFFFF;
      dst->bits[1] = (int_value >> 32) & 0xFFFFFFFF;
      s21_set_scale(dst, scale);
      s21_set_sign(dst, sign);
    }
  }
  return outcome;
}