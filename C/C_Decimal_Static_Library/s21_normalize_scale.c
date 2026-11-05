#include "s21_decimal.h"

int s21_normalize_scale(s21_decimal *a, s21_decimal *b) {
  int scale_a = s21_get_scale(*a);
  int scale_b = s21_get_scale(*b);

  while (scale_a != scale_b) {
    if (scale_a < scale_b) {
      if (scale_a < 28 && s21_increase_scale(a, 1) == 0) {
        scale_a++;
      } else {
        break;
      }
    } else {
      if (scale_b < 28 && s21_increase_scale(b, 1) == 0) {
        scale_b++;
      } else {
        break;
      }
    }
  }

  return 0;
}