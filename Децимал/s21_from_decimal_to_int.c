#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  // Предварительная проверка аргумента
  if (!dst) return 1;

  int outcome = 0;
  s21_decimal truncated = {0};
  s21_truncate(src, &truncated);

  if (truncated.bits[1] || truncated.bits[2]) {
    outcome = 1;
  } else {
    unsigned int val = truncated.bits[0];
    if (s21_get_sign(truncated)) {
      if (val > 2147483648U) outcome = 1;
      if (!outcome) *dst = (val == 2147483648U) ? -2147483648 : -(int)val;
    } else {
      if (val > 2147483647U) outcome = 1;
      if (!outcome) *dst = val;
    }
  }
  return outcome;
}