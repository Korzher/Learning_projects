#include "s21_decimal.h"

long double s21_fmodl(long double x, long double y) {
    // Предварительная проверка аргумента
    if (y == 0.0L) return x;

    long long quotient = (long long)(x / y);
    long double remainder = x - (long double)quotient * y;

    if (remainder == 0.0L)
        remainder = 0.0L * x;
    return remainder;
}