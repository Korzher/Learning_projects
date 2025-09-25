#include "s21_decimal.h"

int s21_compare(s21_decimal a, s21_decimal b) {
  // Предварительная проверка аргумента
  if (s21_is_zero(a) && s21_is_zero(b)) {
    return 0;
  }

  int result = 0;
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  if (sign_a > sign_b) result = -1;
  if (sign_a < sign_b) result = 1;

  if (!result) {
    s21_decimal temp_a = a, temp_b = b;
    s21_normalize_scale(&temp_a, &temp_b);

    for (int i = 2; i >= 0; i--) {
      if (temp_a.bits[i] > temp_b.bits[i]) {
        result = sign_a ? -1 : 1;
        break;
      }
      if (temp_a.bits[i] < temp_b.bits[i]) {
        result = sign_a ? 1 : -1;
        break;
      }
    }
  }
  return result;
}

int s21_compare_abs(s21_decimal a, s21_decimal b) {
  s21_decimal a_abs = a, b_abs = b;
  s21_set_sign(&a_abs, 0);
  s21_set_sign(&b_abs, 0);
  return s21_compare(a_abs, b_abs);
}

int s21_compare_bits(s21_decimal a, s21_decimal b) {
  int outcome = 0;
  for (int j = 2; j >= 0; j--) {
    if (a.bits[j] > b.bits[j]) outcome = 1;
    if (a.bits[j] < b.bits[j]) outcome = -1;
    if (outcome) break;
  }
  return outcome;
}

int s21_is_less(s21_decimal a, s21_decimal b) { return s21_compare(a, b) < 0; }
int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) <= 0;
}
int s21_is_greater(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) > 0;
}
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) >= 0;
}
int s21_is_equal(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) == 0;
}
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) != 0;
}