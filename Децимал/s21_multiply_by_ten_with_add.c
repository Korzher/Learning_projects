#include "s21_decimal.h"

int s21_multiply_by_ten_with_add(s21_decimal *value, uint32_t luggage) {
  // Предварительная проверка аргумента
  if (!value) return 1;

  uint64_t carry = luggage;
  int outcome = 0;

  for (int i = 0; i < 3; i++) {
    uint64_t res = ((uint64_t)value->bits[i]) * 10 + carry;
    value->bits[i] = (uint32_t)(res & 0xFFFFFFFFu);
    carry = res >> 32;
  }

  if (carry != 0) {
    outcome = 1;
  }

  return outcome;
}