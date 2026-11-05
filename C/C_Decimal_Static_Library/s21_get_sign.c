#include "s21_decimal.h"

int s21_get_sign(s21_decimal value) {
  int result = 0;
  if (value.bits[3] & (1 << 31)) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
};