#include "s21_decimal.h"

long double s21_roundl(long double x) {
    return (x >= 0.0L)
        ? (long double)((long long)(x + 0.5L))
        : (long double)((long long)(x - 0.5L));
}