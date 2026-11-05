#include "s21_decimal.h"

int s21_increase_scale(s21_decimal *value, int delta) {
  // Предварительная проверка аргумента
  if (!value || delta < 0) return 1;

  int outcome = 0;

  int current_scale = s21_get_scale(*value);
  if (current_scale + delta > 28) outcome = 1;

  if (s21_is_zero(*value) && !outcome) {
    s21_set_scale(value, current_scale + delta);
  }

  for (int i = 0; i < delta; i++) {
    if (s21_multiply_by_ten_with_add(value, 0) != 0) {
      outcome = 1;
    }
  }

  if (!outcome) s21_set_scale(value, current_scale + delta);
  return outcome;
}