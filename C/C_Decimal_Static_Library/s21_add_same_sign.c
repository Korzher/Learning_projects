#include "s21_decimal.h"

int s21_add_same_sign(s21_decimal a, s21_decimal b, s21_decimal *result,
                      int scale, int sign_a) {
  uint64_t carry = 0;
  int outcome = 0;

  for (int i = 0; i < 3; ++i) {
    uint64_t sum = (uint64_t)a.bits[i] + (uint64_t)b.bits[i] + carry;
    result->bits[i] = (uint32_t)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
  }

  while (carry && scale > 0) {
    s21_decimal temp = *result;
    s21_set_scale(&temp, scale);
    s21_decimal rounded = {0};
    s21_bank_round(temp, &rounded);
    carry = 0;
    for (int i = 0; i < 3; ++i) result->bits[i] = rounded.bits[i];
    scale--;
  }

  if (carry) {
    outcome = sign_a ? 2 : 1;
  } else {
    s21_set_scale(result, scale);
    s21_set_sign(result, sign_a);
    outcome = 0;
  }
  return outcome;
}