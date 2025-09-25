#include "s21_decimal.h"

int s21_bank_round(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_scale(value);
  if (scale == 0) {
    *result = value;
  } else {
    s21_decimal quotient;
    int remainder;
    s21_divide_by_ten(&value, &quotient, &remainder);

    int round_up = 0;
    if (remainder > 5 || (remainder == 5 && (quotient.bits[0] & 1)))
      round_up = 1;

    if (round_up) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_set_scale(&one, 0);
      if (s21_get_sign(value)) {
        s21_sub(quotient, one, result);
      } else {
        s21_add(quotient, one, result);
      }
    } else {
      *result = quotient;
    }

    s21_set_sign(result, s21_get_sign(value));
    s21_set_scale(result, 0);
  }
  return 0;
}

void s21_bank_round96(uint64_t *temp, int *scale) {
  uint64_t rem = 0;
  for (int i = 5; i >= 0; i--) {
    uint64_t full = (rem << 32) | temp[i];
    temp[i] = full / 10;
    rem = full % 10;
  }
  if (rem > 5 || (rem == 5 && (temp[0] & 1))) {
    uint64_t carry = 1;
    for (int i = 0; i < 6 && carry; i++) {
      uint64_t tmp = temp[i] + carry;
      temp[i] = tmp & 0xFFFFFFFF;
      carry = tmp >> 32;
    }
  }
  (*scale)--;
}