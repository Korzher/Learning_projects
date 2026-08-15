#include "s21_decimal.h"

void s21_simple_mul(uint64_t* temp, s21_decimal value_1, s21_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uint64_t mult = (uint64_t)value_1.bits[i] * value_2.bits[j];
      temp[i + j] += mult;
      for (int k = i + j; k < 5; k++) {
        if (temp[k] > 0xFFFFFFFF) {
          temp[k + 1] += temp[k] >> 32;
          temp[k] &= 0xFFFFFFFF;
        } else {
          break;
        }
      }
    }
  }
}