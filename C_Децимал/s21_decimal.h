#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>  // Для int32_t, uint32_t и т.д.
#include <math.h>
#include <string.h>

// Константы для работы с масштабом и знаком
#define S21_DECIMAL_BITS 4                    // 4 × 32 бита = 128 бит всего
#define S21_DECIMAL_SCALE_MAX 28              // Максимальный масштаб (10^28)
#define S21_DECIMAL_SCALE_MASK 0x00FF0000     // Маска для битов 16–23 (масштаб)
#define S21_DECIMAL_SIGN_BIT 0x80000000       // Бит 31 — знак

// Основная структура: 128-битное десятичное число с плавающей точкой
typedef struct {
    uint32_t bits[S21_DECIMAL_BITS];  // bits[0]–[2]: 96-битное целое, bits[3]: масштаб и знак
} s21_decimal;

// --- Арифметические операции ---
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// --- Операторы сравнения ---
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

// --- Преобразования типов ---
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// --- Другие функции ---
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// --- Вспомогательные функции (для тестов и внутреннего использования) ---
int s21_get_scale(s21_decimal value);
int s21_get_sign(s21_decimal d);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_sign(s21_decimal *value, int sign);
int s21_is_zero(s21_decimal value);
int s21_divide_by_ten(s21_decimal *dividend, s21_decimal *quotient, int *remainder);
int s21_is_valid(s21_decimal dec);
int s21_compare_abs(s21_decimal a, s21_decimal b);
int s21_compare_bits(s21_decimal a, s21_decimal b);
int s21_bank_round(s21_decimal value, s21_decimal *result);
void s21_bank_round96(uint64_t *temp, int *scale);
int s21_normalize_scale(s21_decimal *value_1, s21_decimal *value_2);
int s21_increase_scale(s21_decimal *value, int delta);
int s21_highest_bit(s21_decimal value);
int s21_add_same_sign(s21_decimal a, s21_decimal b, s21_decimal *result, int scale, int sign_a);
int s21_add_diff_sign(s21_decimal a, s21_decimal b, s21_decimal *result, int scale);
int s21_simple_div(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient, s21_decimal *remainder);
void s21_shift_left(s21_decimal *dec);
void s21_shift_right(s21_decimal *dec);
void s21_subtract_raw_bits(s21_decimal *a, s21_decimal b);
void s21_simple_mul(uint64_t *temp, s21_decimal value_1, s21_decimal value_2);
int s21_multiply_by_ten_with_add(s21_decimal *value, uint32_t luggage);
long double s21_fmodl(long double x, long double y);
long double s21_roundl(long double x);

#endif  // S21_DECIMAL_H
