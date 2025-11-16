#include "s21_decimal.h"

int s21_is_valid(s21_decimal dec) {
  int valid = 1;
  uint32_t fourth_part = (uint32_t)dec.bits[3];
  if ((fourth_part & 0x0000FFFF) != 0) {
    valid = 0;
  }
  uint32_t exponent = (fourth_part >> 16) & 0xFF;
  if (exponent > 28) {
    valid = 0;
  }
  if ((fourth_part & 0x7F000000) != 0) {
    valid = 0;
  }
  return valid;
}