#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Предварительные проверки аргументов
  if (!result) return 1;
  if (!s21_is_valid(value_1) || !s21_is_valid(value_2)) return 1;
  int outcome = 0;
  memset(result, 0, sizeof(s21_decimal));

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);
  int scale = scale1 + scale2;

  if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
    s21_set_scale(result, 0);
    s21_set_sign(result, sign1 ^ sign2);
  } else {
    uint64_t temp[6] = {0};
    s21_simple_mul(temp, value_1, value_2);

    int overflow = (temp[3] || temp[4] || temp[5]) || (scale > 28);
    while (overflow && scale > 0) {
      s21_bank_round96(temp, &scale);
      overflow = (temp[3] || temp[4] || temp[5]) || (scale > 28);
    }

    if (overflow) {
      outcome = (sign1 ^ sign2) ? 2 : 1;
    } else {
      result->bits[0] = (uint32_t)temp[0];
      result->bits[1] = (uint32_t)temp[1];
      result->bits[2] = (uint32_t)temp[2];
      s21_set_scale(result, scale);
      s21_set_sign(result, sign1 ^ sign2);
    }
  }
  return outcome;
}