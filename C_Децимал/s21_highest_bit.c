#include "s21_decimal.h"

int s21_highest_bit(s21_decimal value) {
  int highest_bit = 95;
  while (highest_bit >= 0 &&
         !((value.bits[highest_bit / 32] >> (highest_bit % 32)) & 1))
    highest_bit--;

  return highest_bit;
}