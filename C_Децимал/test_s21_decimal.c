#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

#include "s21_decimal.h"

/*  Runner:
***        - Suite: Transform
***            -Testcase: from_int_do_decimal
***               - Test: from_int_to_decimal корректно переводит десятичное
*число в int
***                - Test: from_int_to_decimal корректно переводит отрицательный
*int в десятичное число
***                - Test: from_int_to_decimal корректно переводит ноль в
*десятичное число
***                - Test: from_int_to_decimal корректно переводит максимальный
*int в десятичное число
***                - Test: from_int_to_decimal корректно переводит минимальный
*int в десятичное число
***                - Test: from_int_to_decimal корректно отрабатывает ошибку
*аргумента
***                - Test: from_int_to_decimal корректно переводит единицу в
*десятичное число
***                - Test: from_int_to_decimal корректно переводит минус единицу
*в десятичное число
***            -Testcase: from_decimal_to_int
***                - Test: from_decimal_to_int корректно переводит десятичное
*число в int
***                - Test: from_decimal_to_int корректно переводит отрицательное
*десятичное число в int
***                - Test: from_decimal_to_int корректно переводит ноль из
*десятичного числа в int
***                - Test: from_decimal_to_int корректно отсекает дробную часть
*отрицательного в int
***                - Test: from_decimal_to_int корректно отсекает дробную часть
*положительного в int
***                - Test: from_decimal_to_int корректно отсекает дробную часть
*большого числа в int
***                - Test: from_decimal_to_int корректно переводит максимальный
*int в int
***                - Test: from_decimal_to_int корректно переводит минимальный
*int в int
***                - Test: from_decimal_to_int корректно обрабатывает
*положительный overflow
***                - Test: from_decimal_to_int корректно обрабатывает
*отрицательный overflow
***                - Test: from_decimal_to_int корректно обрабатывает null в
*аргументе
***                - Test: Test: from_decimal_to_int корректно обрабатывает
*ненулевой старший бит
***            -Testcase: from_float_to_decimal
***                - Test: from_float_to_decimal корректно переводит float в
*десятичное число
***                - Test: from_float_to_decimal корректно переводит
*отрицательный float в десятичное число
***                Test: from_float_to_decimal корректно переводит ноль в
*десятичное число
***                Test: from_float_to_decimal корректно переводит максимальный
*float в десятичное число
***                Test: from_float_to_decimal корректно переводит минимальный
*float в десятичное число
***                Test: from_float_to_decimal корректно отрабатывает ошибку
*аргумента
***                Test: from_float_to_decimal корректно переводит float единицу
*в десятичное число
***                Test: from_float_to_decimal корректно переводит float минус
*единицу в десятичное число
***            -Testcase: from_decimal_to_float
***                - Test: from_decimal_to_float корректно переводит десятичное
*число в float
***                - Test: from_decimal_to_float корректно переводит
*отрицательное десятичное число в float
***                Test: from_decimal_to_float корректно переводит ноль в float
***                Test: from_decimal_to_float корректно переводит большое число
***                Test: from_decimal_to_float корректно переводит маленькое
*число
***                Test: from_decimal_to_float корректно отрабатывает ошибку
*аргумента
***                Test: from_decimal_to_float корректно переводит единицу в
*float
***                Test: from_decimal_to_float корректно переводит минус единицу
*в float
***                Test: проверка точности конвертации с большим scale
***                Test: максимальный scale (28 знаков после запятой)
***                Test: from_decimal_to_float корректно переводит максимальный
*точный целый float
***                Test: from_decimal_to_float корректно переводит число с
*большим scale
***        - Suite: Arithmetic
***            -Testcase: s21_add
***                - Test: s21_add корректно отрабатывает сложение двух
*децималов
***               - Test: s21_add корректно обрабатывает сложение двух
*децималов, где первый отрицательный
***                - Test: s21_add корректно обрабатывает сложение двух
*децималов, где второй отрицательный
***                - Test: s21_add корректно обрабатывает сложение двух
*децималов, где оба отрицательные
***                - Test: s21_add корректно обрабатывает overflow вверх
***                - Test: s21_add корректно обрабатывает overflow вниз
***            -Testcase: s21_sub
***                - Test: s21_sub корректно отрабатывает вычитание двух
*децималов
***                - Test: s21_sub корректно обрабатывает вычитание, где первый
*отрицательный
***                - Test: s21_sub корректно обрабатывает вычитание, где второй
*отрицательный
***                - Test: s21_sub корректно обрабатывает вычитание, где оба
*отрицательные
***                - Test: s21_sub корректно обрабатывает overflow вверх
***                - Test: s21_sub корректно обрабатывает overflow вниз
***                - Test: s21_sub корректно обрабатывает вычитание равных чисел
***                - Test: s21_sub корректно обрабатывает вычитание нуля из
*положительного числа
***                - Test: s21_sub корректно обрабатывает вычитание нуля из
*отрицательного числа
***                - Test: s21_sub корректно обрабатывает вычитание
*положительного из нуля
***                - Test: s21_sub корректно обрабатывает вычитание
*отрицательного из нуля
***            -Testcase: s21_mul
***                - Test: s21_mul корректно отрабатывает умножение двух
*положительных децималов
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где первый отрицательный
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где второй отрицательный
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где оба отрицательные
***                - Test: s21_mul корректно обрабатывает умножение на 0
***                - Test: s21_mul корректно обрабатывает умножение на 1
***                - Test: s21_mul корректно обрабатывает overflow вверх
***                - Test: s21_mul корректно обрабатывает overflow вниз
***            -Testcase: s21_div
***                - Test: s21_div корректно делит два децимала
***                - Test: s21_div корректно делит два децимала, где первый
*отрицательный
***                - Test: s21_div корректно делит два децимала, где второй
*отрицательный
***                - Test: s21_div корректно делит два децимала, где оба
*отрицательные
***                - Test: s21_div корректно делит два децимала, где второй ноль
***                - Test: s21_div корректно делит два децимала, где первый ноль
***                - Test: s21_div корректно делит децимал на единицу
***        - Suite: Float_arithmetic:
***            -Testcase: s21_fadd
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, где первый отрицательный
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, где второй отрицательный
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, где оба отрицательные
***                - Test: s21_add корректно обрабатывает overflow с плавающей
*точкой вверх
***                - Test: s21_add корректно обрабатывает overflow с плавающей
*точкой вниз
***                - Test: s21_add корректно добавляет два 0 с плавающей точкой
***                - Test: s21_add корректно добавляет к 0 с плавающей точкой
***                - Test: s21_add корректно добавляет 0 с плавающей точкой
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, с разными степенями
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, с очень маленькими значениями
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, с очень разными степенями
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, с очень большими значениями близкими к overflow
***                - Test: s21_add корректно добавляет два децимала с плавающей
*точкой, с отрицательным переполением
***                - Test: s21_add корректно отрабатывает потерю точности
***                - Test: s21_add корректно отрабатывает сложение малых чисел
***                - Test: s21_add корректно отрабатывает очень большие числа,
*близкие к переполнению
***                - Test: s21_add корректно отрабатывает очень малые числа,
*близкие к минус бесконечности
***            -Testcase: s21_fsub
***                - Test: s21_sub корректно вычитает два децимала с плавающей
*точкой
***                - Test: s21_sub корректно вычитает два децимала, где первый
*отрицательный
***                - Test: s21_sub корректно вычитает два децимала, где второй
*отрицательный
***                - Test: s21_sub корректно вычитает два децимала, где оба
*отрицательные
***                - Test: s21_sub корректно отрабатывает положительное
*переполнение
***                - Test: s21_sub корректно отрабатывает отрицательное
*переполнение
***                - Test: s21_sub корректно вычитает два нуля
***                - Test: s21_sub корректно вычитает из нуля
***                - Test: s21_sub корректно вычитает ноль
***                - Test: s21_sub корректно вычитает два децимала, где один
*имеет больший scale
***                - Test: s21_sub корректно вычитает два децимала, где оба
*имеют очень маленькие значения
***                - Test: s21_sub корректно вычитает два децимала, где один
*имеет больший scale
***                - Test: s21_sub корректно вычитает два децимала в значениях
*приближенных к переполнению
***                - Test: s21_sub корректно вычитает два децимала, где один
*имеет отрицательное значение и больший масштаб
***                - Test: s21_sub корректно вычитает два децимала, с
*сохранением точности
***                - Test: s21_sub корректно вычитает два децимала, где один
*имеет высокую точность
***                - Test: s21_sub корректно вычитает два децимала, приближенных
*к минимальным значениям
***                - Test: s21_sub корректно вычитает два децимала, приближенных
*к нулю
***                - Test: s21_sub корректно занимает биты
***                - Test: s21_sub корректно вычитает два децимала, приближенных
*с малыми значениями
***                - Test: s21_sub корректно вычитает два одинаковых децимала
***                - Test: s21_sub корректно округляет децималы
***            -Testcase: s21_fmul
***                - Test: s21_mul корректно умножает два децимала
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где первый отрицательный
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где второй отрицательный
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов, где оба отрицательные
***                - Test: s21_mul корректно обрабатывает overflow вверх
***                - Test: s21_mul корректно обрабатывает overflow вниз
***                - Test: s21_mul корректно обрабатывает умножение на 0
***                - Test: s21_mul корректно обрабатывает умножение двух нолей
***                - Test: s21_mul корректно обрабатывает умножение на 1
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов с разными scale
***                - Test: s21_mul корректно обрабатывает умножение двух очень
*маленьких децималов
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов с большими scale
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов c переполнением
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов с различным scale, где один отрицательный
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов с высокой точностью
***                - Test: s21_mul корректно обрабатывает умножение двух
*децималов с переполнением scale
***                - Test: s21_mul корректно обрабатывает умножение двух единиц
*с большим значением scale
***                - Test: s21_mul корректно обрабатывает умножение двух
*одинаковых децималов
***                - Test: s21_mul корректно обрабатывает умножение на число в
*степени 10
***                - Test: s21_float_mul корректно обрабатывает умножение двух
*очень малых децималов
***            -Testcase: s21_fdiv
***                - Test: s21_div корректно делит два децимала
***                - Test: s21_div корректно делит два децимала, где первый
*отрицательный
***                - Test: s21_div корректно делит два децимала, где второй
*отрицательный
***                - Test: s21_div корректно делит два децимала, где оба
*отрицательные
***                - Test: s21_div корректно делит децимал на ноль
***                - Test: s21_div корректно делит ноль на децимал
***                - Test: s21_div корректно делит децимал на единицу
***                - Test: s21_div корректно делит децималы с разными масштабами
***                - Test: s21_div корректно делит децималы с маленькими числами
***                - Test: s21_div корректно делит децималы с большим масштабом
***                - Test: s21_div корректно делит отрицательный децимал на
*число с меньшим масштабом
***                - Test: s21_div корректно делит децималы с очень большим
*масштабом
***                - Test: s21_div корректно управляет масштабом
***                - Test: s21_div корректно делит децималы с очень большими
*числами
***                - Test: s21_div корректно отрабатывает дробную часть
***                - Test: s21_div корректно делит децимал с максимальным
*масштабом
***                - Test: s21_div корректно делит децимал на степень десяти
***                - Test: s21_div корректно делит децимал на очень маленький
*децимал
***                - Test: s21_div корректно делит децималы с нормализацией
***                - Test: s21_div корректно делит два децимала с максимальным
*масштабом
***                - Test: s21_div корректно делит децималы с периодической
*дробью
***                - Test: s21_div корректно делит децималы с большими целыми
***                - Test: s21_div корректно делит децимал на -1
***                - Test: s21_div корректно делит децималы с огромным числом
***                - Test: s21_div корректно делит децималы с одинаковой
*точностью
***                - Test: s21_div корректно обрабатывает переполнение
***        - Suite: Comparison
***            -Testcase: s21_is_equal
***                - Test: s21_is_equal корректно сравнивает равные
***                - Test: s21_is_equal корректно сравнивает равные с разным
*масштабом
***                - Test: s21_is_equal корректно сравнивает положительный и
*отрицательный ноль
***            - Test: s21_is_less
***                - Test: s21_is_less корректно сравнивает положительные числа
***                - Test: s21_is_less корректно сравнивает отрицательные числа
***                - Test: s21_is_less корректно сравнивает числа с разными
*знаками
***                - Test: s21_is_less корректно сравнивает равные значения
***                - Test: s21_is_less корректно сравнивает числа с разными
*масштабами
***                - Test: s21_is_less корректно сравнивает с нулем
***            - Test: s21_is_greater
***                - Test: s21_is_greater корректно сравнивает положительные
***                - Test: s21_is_greater корректно сравнивает отрицательные
***            - Test: s21_is_less_or_equal
***                - Test: s21_is_less_or_equal корректно сравнивает
*положительные числа
***                - Test: s21_is_less_or_equal корректно сравнивает одинаковые
*числа
***            - Test: s21_is_greater_or_equal
***                - Test: s21_is_greater_or_equal корректно сравнивает равные
***            - Test: s21_is_not_equal
***                - Test: s21_is_not_equal корректно сравнивает разные числа
***        - Suite: Additional
***            -Testcase: s21_floor
***                - Test: s21_floor корректно округляет положительные
***                - Test: s21_floor корректно округляет отрицательные
***            - Testcase: s21_round
***                - Test: s21_round корректно округляет вверх
***                - Test: s21_round корректно округляет вниз
***            - Testcase: s21_truncate
***                - Test: s21_truncate корректно отрезает нули
***            - Testcase: s21_negate
***                - Test: s21_negate корректно меняет знак
*/

START_TEST(test_s21_from_int_to_dec_base) {
  // Test: from_int_to_decimal корректно переводит int в десятичное число
  int number = 10;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], 10);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
  ck_assert_uint_eq(decimal.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_negative_int) {
  // Test: from_int_to_decimal корректно переводит отрицательный int в
  // десятичное число
  int number = -10;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], 10);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
  ck_assert_uint_eq(decimal.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_from_zero_int) {
  // Test: from_int_to_decimal корректно переводит ноль в десятичное число
  int number = 0;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
  ck_assert_uint_eq(decimal.bits[3], 0);
}
END_TEST

START_TEST(test_s21_max_int) {
  // Test: from_int_to_decimal корректно переводит максимальный int в десятичное
  // число
  int number = INT_MAX;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], INT_MAX);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
  ck_assert_uint_eq(decimal.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test_s21_min_int) {
  // Test: from_int_to_decimal корректно переводит минимальный int в десятичное
  // число
  int number = INT_MIN;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], (unsigned int)INT_MIN);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
  ck_assert_uint_eq(decimal.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_itod_null_dst) {
  // Test: from_int_to_decimal корректно отрабатывает ошибку аргумента
  int number = 42;
  int outcome = s21_from_int_to_decimal(number, NULL);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_one) {
  // Test: from_int_to_decimal корректно переводит единицу в десятичное число
  int number = 1;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], 1);
  ck_assert_uint_eq(decimal.bits[3], 0);
}
END_TEST

START_TEST(test_s21_minus_one) {
  // Test: from_int_to_decimal корректно переводит минус единицу в десятичное
  // число
  int number = -1;
  s21_decimal decimal = {{0}};
  int outcome = s21_from_int_to_decimal(number, &decimal);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(decimal.bits[0], 1);
  ck_assert_uint_eq(decimal.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_positive_decimal_to_int) {
  // Test: from_decimal_to_int корректно переводит десятичное число в int
  s21_decimal dec = {{21, 0, 0, 0}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result, 21);
}
END_TEST

START_TEST(test_s21_negative_decimal_to_int) {
  // Test: from_decimal_to_int корректно переводит отрицательное десятичное
  // число в int
  s21_decimal dec = {{21, 0, 0, 1 << 31}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result, -21);
}
END_TEST

START_TEST(test_s21_zero_decimal_to_int) {
  // Test: from_decimal_to_int корректно переводит ноль из десятичного числа в
  // int
  s21_decimal dec = {{0, 0, 0, 0}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_truncates_fractional_negative) {
  // Test: from_decimal_to_int корректно отсекает дробную часть отрицательного в
  // int
  s21_decimal dec_neg = {{19, 0, 0, 1 << 31 | 1 << 16}};
  int result_neg = 0;
  int outcome_neg = s21_from_decimal_to_int(dec_neg, &result_neg);
  ck_assert_int_eq(outcome_neg, 0);
  ck_assert_int_eq(result_neg, -1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_truncates_fractional_positive) {
  // Test: from_decimal_to_int корректно отсекает дробную часть положительного в
  // int
  s21_decimal dec_pos = {{19, 0, 0, 1 << 16}};
  int result_pos = 0;
  int outcome_pos = s21_from_decimal_to_int(dec_pos, &result_pos);
  ck_assert_int_eq(outcome_pos, 0);
  ck_assert_int_eq(result_pos, 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_truncates_fractional_large) {
  // Test: from_decimal_to_int корректно отсекает дробную часть большого числа в
  // int
  s21_decimal dec_large = {{123456789, 0, 0, 3 << 16}};
  int result_large = 0;
  int outcome_large = s21_from_decimal_to_int(dec_large, &result_large);
  ck_assert_int_eq(outcome_large, 0);
  ck_assert_int_eq(result_large, 123456);
}
END_TEST

START_TEST(test_s21_max_int_to_decimal) {
  // Test: from_decimal_to_int корректно переводит максимальный int в int
  s21_decimal dec = {{2147483647, 0, 0, 0}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result, 2147483647);
}
END_TEST

START_TEST(test_s21_min_int_to_decimal) {
  // Test: from_decimal_to_int корректно переводит минимальный int в int
  s21_decimal dec = {
      {2147483648U, 0, 0, 1 << 31}};  // INT_MIN (бит знака установлен)
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result, -2147483648);
}
END_TEST

START_TEST(test_s21_overflow_positive) {
  // Test: from_decimal_to_int корректно обрабатывает положительный overflow
  s21_decimal dec = {{2147483648U, 0, 0, 0}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_overflow_negative) {
  // Test: from_decimal_to_int корректно обрабатывает отрицательный overflow
  s21_decimal dec = {{2147483649U, 0, 0, 1 << 31}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_dtoi_null_dst) {
  // Test: from_decimal_to_int корректно обрабатывает null в аргументе
  s21_decimal dec = {{21, 0, 0, 0}};
  int outcome = s21_from_decimal_to_int(dec, NULL);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_non_zero_high_bits) {
  // Test: from_decimal_to_int корректно обрабатывает ненулевой старший бит
  s21_decimal dec = {{21, 1, 0, 0}};
  int result = 0;
  int outcome = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_ftod_basic_positive) {
  // Test: from_float_to_decimal корректно переводит float в десятичное число
  float number = 42.5f;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 425);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);

  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 1);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_s21_ftod_negative) {
  // Test: from_float_to_decimal корректно переводит отрицательный float в
  // десятичное число
  float number = -123.75f;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);

  ck_assert_uint_eq(result.bits[0], 12375);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);

  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 2);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_ftod_zero) {
  // Test: from_float_to_decimal корректно переводит ноль в десятичное число
  float number = 0.0f;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);

  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 0);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_s21_ftod_max_float) {
  // Test: from_float_to_decimal корректно переводит максимальный float в
  // десятичное число
  float number = FLT_MAX;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_ftod_min_float) {
  // Test: from_float_to_decimal корректно переводит минимальный float в
  // десятичное число
  float number = FLT_MIN;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);
  s21_is_zero(result);
}
END_TEST

START_TEST(test_s21_ftod_null_dst) {
  // Test: from_float_to_decimal корректно отрабатывает ошибку аргумента
  float number = 42.5f;
  int outcome = s21_from_float_to_decimal(number, NULL);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_ftod_one) {
  // Test: from_float_to_decimal корректно переводит float единицу в десятичное
  // число
  float number = 1.0f;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 0);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_s21_ftod_minus_one) {
  // Test: from_float_to_decimal корректно переводит float минус единицу в
  // десятичное число
  float number = -1.0f;
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(number, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 0);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_ftod_low_one) {
  // Test: from_float_to_decimal корректно переводит float минус единицу в
  // десятичное число
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(0.0000001f, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 7);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_s21_ftod_trailing_zeros) {
  // Test: from_float_to_decimal корректно удаляет ведущие нули
  s21_decimal result = {0};
  int outcome = s21_from_float_to_decimal(3.6000f, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 36);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq((result.bits[3] >> 16) & 0xFF, 1);
  ck_assert_uint_eq((result.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_s21_dtof_basic_positive) {
  // Test: from_decimal_to_float корректно переводит десятичное число в float
  s21_decimal decimal = {0};
  decimal.bits[0] = 425;
  decimal.bits[3] = 1 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 42.5f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_negative) {
  // Test: from_decimal_to_float корректно переводит отрицательное десятичное
  // число в float
  s21_decimal decimal = {0};
  decimal.bits[0] = 12375;
  decimal.bits[3] = (1 << 31) | (2 << 16);

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, -123.75f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_zero) {
  // Test: from_decimal_to_float корректно переводит ноль в float
  s21_decimal decimal = {0};

  float result = 1.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 0.0f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_large_number) {
  // Test: from_decimal_to_float корректно переводит большое число
  s21_decimal decimal = {0};
  decimal.bits[0] = 123456789;
  decimal.bits[3] = 3 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 123456.789f, 1e-3f);
}
END_TEST

START_TEST(test_s21_dtof_small_number) {
  // Test: from_decimal_to_float корректно переводит маленькое число
  s21_decimal decimal = {0};
  decimal.bits[0] = 123;
  decimal.bits[3] = 6 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 0.000123f, 1e-9f);
}
END_TEST

START_TEST(test_s21_dtof_null_dst) {
  // Test: from_decimal_to_float корректно отрабатывает ошибку аргумента
  s21_decimal decimal = {0};
  decimal.bits[0] = 42;
  decimal.bits[3] = 0;

  int outcome = s21_from_decimal_to_float(decimal, NULL);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_dtof_one) {
  // Test: from_decimal_to_float корректно переводит единицу в float
  s21_decimal decimal = {0};
  decimal.bits[0] = 1;
  decimal.bits[3] = 0;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 1.0f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_minus_one) {
  // Test: from_decimal_to_float корректно переводит минус единицу в float
  s21_decimal decimal = {0};
  decimal.bits[0] = 1;
  decimal.bits[3] = 1 << 31;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, -1.0f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_precision) {
  // Test: проверка точности конвертации с большим scale
  s21_decimal decimal = {0};
  decimal.bits[0] = 314159265;
  decimal.bits[3] = 8 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 3.14159265f, 1e-8f);
}
END_TEST

START_TEST(test_s21_dtof_max_scale) {
  // Test: максимальный scale (28 знаков после запятой)
  s21_decimal decimal = {0};
  decimal.bits[0] = 1;
  decimal.bits[3] = 28 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 1e-28f, 1e-30f);
}
END_TEST

START_TEST(test_s21_dtof_within_float_precision) {
  // Test: from_decimal_to_float корректно переводит максимальный точный целый
  // float
  s21_decimal decimal = {0};
  decimal.bits[0] = 16777215;
  decimal.bits[3] = 0;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 16777215.0f, 1e-6f);
}
END_TEST

START_TEST(test_s21_dtof_large_with_scale) {
  // Test: from_decimal_to_float корректно переводит число с большим scale
  s21_decimal decimal = {0};
  decimal.bits[0] = 123456789;
  decimal.bits[1] = 0;
  decimal.bits[3] = 3 << 16;

  float result = 0.0f;
  int outcome = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result, 123456.789f, 1e-3f);
}
END_TEST

START_TEST(test_s21_add_positive) {
  // Test: s21_add корректно отрабатывает сложение двух децималов
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{21, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 42);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_first_negative) {
  // Test: s21_add корректно отрабатывает сложение двух децималов, где первый
  // отрицательный
  s21_decimal a = {{5, 0, 0, 1 << 31}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 2);
  ck_assert_uint_eq(result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_add_second_negative) {
  // Test: s21_add корректно отрабатывает сложение двух децималов, где второй
  // отрицательный
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 2);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_both_negative) {
  // Test: s21_add корректно отрабатывает сложение двух децималов, где оба
  // отрицательные
  s21_decimal a = {{5, 0, 0, 1 << 31}};
  s21_decimal b = {{3, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 8);
  ck_assert_uint_eq(result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_add_overflow_positive) {
  // Test: s21_add корректно обрабатывает overflow вверх
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_add_overflow_negative) {
  // Test: s21_add корректно обрабатывает overflow вниз
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 1 << 31}};
  s21_decimal b = {{1, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 2);
}
END_TEST

START_TEST(test_s21_add_zero) {
  // Test: s21_add корректно обрабатывает сложение двух нулевых децималов
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_add_zero_first) {
  // Test: s21_add корректно обрабатывает сложение с нулем
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{21, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 21);
}
END_TEST

START_TEST(test_s21_add_zero_second) {
  // Test: s21_add корректно обрабатывает прибавление нуля
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 21);
}
END_TEST

START_TEST(test_s21_add_first_bit_overflow) {
  // Test: s21_add корректно переносит из первого бита во второй
  s21_decimal a = {{4294967295, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 1);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_second_bit_overflow) {
  // Test: s21_add корректно переносит из второго бита в третий
  s21_decimal a = {{4294967295, 4294967295, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 1);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_negative_large_numbers) {
  // Test: s21_add корректно вычитает из старшего бита
  s21_decimal a = {{0, 1, 0, 1 << 31}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 4294967295);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_add_two_large_numbers) {
  // Test: s21_add корректно складывает два больших числа
  s21_decimal a = {{4294967295, 1, 0, 0}};
  s21_decimal b = {{4294967295, 0, 0, 0}};
  s21_decimal res = {{0}};
  int outcome = s21_add(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 4294967294);
  ck_assert_uint_eq(res.bits[1], 2);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_two_positive_numbers) {
  // Test: s21_sub корректно отрабатывает вычитание двух децималов
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 11);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_first_negative) {
  // Test: s21_sub корректно обрабатывает вычитание, где первый отрицательный
  s21_decimal a = {{21, 0, 0, 1 << 31}};
  s21_decimal b = {{21, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 42);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_sub_second_negative) {
  // Test: s21_sub корректно обрабатывает вычитание, где второй отрицательный
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{21, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 42);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_both_negative) {
  // Test: s21_sub корректно обрабатывает вычитание, где оба отрицательные
  s21_decimal a = {{21, 0, 0, 1 << 31}};
  s21_decimal b = {{20, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_sub_overflow_up) {
  // Test: s21_sub корректно обрабатывает overflow вверх
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal b = {{1, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_sub_overflow_down) {
  // Test: s21_sub корректно обрабатывает overflow вниз
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 1 << 31}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 2);
}
END_TEST

START_TEST(test_s21_sub_equal_numbers) {
  // Test: s21_sub корректно отрабатывает вычитание равных чисел
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{21, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_zero_from_positive) {
  // Test: s21_sub корректно отрабатывает вычитание нуля из положительного числа
  s21_decimal a = {{21, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 21);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_zero_from_negative) {
  // Test: s21_sub корректно отрабатывает вычитание нуля из отрицательного числа
  s21_decimal a = {{42, 0, 0, 1 << 31}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 42);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_sub_positive_from_zero) {
  // Test: s21_sub корректно отрабатывает вычитание положительного из нуля
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 100);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_sub_negative_from_zero) {
  // Test: s21_sub корректно отрабатывает вычитание отрицательного из нуля
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{21, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_sub(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 21);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_two_positive_numbers) {
  // Test: s21_mul корректно отрабатывает умножение двух положительных децималов
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 56088);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_first_negative) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов, где первый
  // отрицательный
  s21_decimal a = {{10, 0, 0, 1 << 31}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 50);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_mul_second_negative) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов, где второй
  // отрицательный
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 50);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_mul_both_negative) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов, где оба
  // отрицательные
  s21_decimal a = {{10, 0, 0, 1 << 31}};
  s21_decimal b = {{5, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 50);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_with_zero) {
  // Test: s21_mul корректно обрабатывает умножение на 0
  s21_decimal a = {{999, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_by_one) {
  // Test: s21_mul корректно обрабатывает умножение на 1
  s21_decimal a = {{12345, 0, 0, 0}};  // 123.45
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(res.bits[0], 12345);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_overflow_result) {
  // Test: s21_mul корректно обрабатывает overflow вверх
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_mul_underflow_result) {
  // Test: s21_mul корректно обрабатывает overflow вниз
  s21_decimal a = {{4294967295, 4294967295, 4294967295, 1 << 31}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};

  int outcome = s21_mul(a, b, &res);

  ck_assert_int_eq(outcome, 2);
}
END_TEST

START_TEST(test_s21_div_basic) {
  // Test: s21_div корректно делит два децимала
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_s21_div_neg_numerator) {
  // Test: s21_div корректно делит два децимала, где первый отрицательный
  s21_decimal a = {{100, 0, 0, 1 << 31}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result.bits[3] >> 31, 1);
  ck_assert_uint_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_s21_div_neg_denominator) {
  // Test: s21_div корректно делит два децимала, где второй отрицательный
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(result.bits[3] >> 31, 1);
  ck_assert_uint_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_s21_div_both_neg) {
  // Test: s21_div корректно делит два децимала, где оба отрицательные
  s21_decimal a = {{100, 0, 0, 1 << 31}};
  s21_decimal b = {{5, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[3] >> 31, 0);
  ck_assert_uint_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_s21_div_zero_denominator) {
  // Test: s21_div корректно делит два децимала, где второй ноль
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 3);
}
END_TEST

START_TEST(test_s21_div_zero_numerator) {
  // Test: s21_div корректно делит два децимала, где первый ноль
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {{4294967295, 4294967295, 4294967295, 0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_one) {
  // Test: s21_div корректно делит децимал на единицу
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};

  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_uint_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_s21_float_add_positive) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(2.1f, &a);
  s21_from_float_to_decimal(2.1f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 4.2f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_first_negative) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, где
  // первый отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-5.5f, &a);
  s21_from_float_to_decimal(3.2f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -2.3f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_second_negative) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, где
  // второй отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(5.75f, &a);
  s21_from_float_to_decimal(-3.25f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 2.5f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_both_negative) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, где оба
  // отрицательные
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-5.8f, &a);
  s21_from_float_to_decimal(-3.2f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -9.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_overflow_positive) {
  // Test: s21_add корректно обрабатывает overflow с плавающей точкой вверх
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(7.922816251e+28f, &a);
  s21_from_float_to_decimal(1.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
}
END_TEST

START_TEST(test_s21_float_add_overflow_negative) {
  // Test: s21_add корректно обрабатывает overflow с плавающей точкой вниз
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-7.922816251e+28f, &a);
  s21_from_float_to_decimal(-1.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
}
END_TEST

START_TEST(test_s21_float_add_zero) {
  // Test: s21_add корректно добавляет два 0 с плавающей точкой
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_zero_first) {
  // Test: s21_add корректно добавляет к 0 с плавающей точкой
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(21.37f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 21.37f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_zero_second) {
  // Test: s21_add корректно добавляет 0 с плавающей точкой
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(42.24f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 42.24f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_different_scales) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, с
  // разными степенями
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(123.456f, &a);
  s21_from_float_to_decimal(78.9f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 202.356f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_very_small_numbers) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, с очень
  // маленькими значениями
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.000001f, &a);
  s21_from_float_to_decimal(0.000002f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.000003f, 1e-9);
}
END_TEST

START_TEST(test_s21_float_add_large_scale_difference) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, с очень
  // разными степенями
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(123456789, &a);
  s21_set_scale(&a, 6);
  s21_from_int_to_decimal(987, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 133.326789f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_negative_with_scale) {
  // Test: s21_add корректно добавляет два децимала с плавающей точкой, с
  // отрицательным переполением
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(-12345, &a);
  s21_set_scale(&a, 3);
  s21_from_int_to_decimal(6789, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 55.545f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_add_precision_loss) {
  // Test: s21_add корректно отрабатывает потерю точности
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1.23456789f, &a);
  s21_from_float_to_decimal(0.00000001f, &b);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.23457f, 1e-5);
}
END_TEST

START_TEST(test_s21_float_add_max_precision) {
  // Test: s21_add корректно отрабатывает сложение малых чисел
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(999999999, &a);
  s21_set_scale(&a, 8);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 8);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 10.0f, 1e-7);
}
END_TEST

START_TEST(test_s21_float_add_denormalized) {
  // Test: s21_add корректно отрабатывает очень малые числа, близкие к минус
  // бесконечности
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 28);
  s21_decimal result = {0};
  int outcome = s21_add(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(s21_get_scale(result), 28);
}
END_TEST

START_TEST(test_s21_float_add_two_carrying) {
  // Test: s21_add корректно складывает два больших числа
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal b = {{0x00000001, 0x00000000, 0x00000000, 0x00010000}};
  s21_decimal result = {{0}};

  int scale = 1;
  int sign_a = 0;

  int outcome = s21_add_same_sign(a, b, &result, scale, sign_a);
  ck_assert_int_le(outcome, 1);
  ck_assert_int_ge(outcome, 0);
}
END_TEST

START_TEST(test_s21_float_sub_positive) {
  // Test: s21_sub корректно вычитает два децимала с плавающей точкой
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(5.5f, &a);
  s21_from_float_to_decimal(2.3f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 3.2f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_first_negative) {
  // Test: s21_sub корректно вычитает два децимала, где первый отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-5.5f, &a);
  s21_from_float_to_decimal(2.3f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -7.8f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_second_negative) {
  // Test: s21_sub корректно вычитает два децимала, где второй отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(5.5f, &a);
  s21_from_float_to_decimal(-2.3f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 7.8f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_both_negative) {
  // Test: s21_sub корректно вычитает два децимала, где оба отрицательные
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-5.5f, &a);
  s21_from_float_to_decimal(-2.3f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -3.2f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_zero) {
  // Test: s21_sub корректно вычитает два нуля
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_zero_first) {
  // Test: s21_sub корректно вычитает из нуля
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(21.37f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -21.37f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_zero_second) {
  // Test: s21_sub корректно вычитает ноль
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(42.24f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 42.24f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_different_scales) {
  // Test: s21_sub корректно вычитает два децимала, где один имеет больший scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(123.456f, &a);
  s21_from_float_to_decimal(78.9f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 44.556f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_very_small_numbers) {
  // Test: s21_sub корректно вычитает два децимала, где оба имеют очень
  // маленькие значения
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.000003f, &a);
  s21_from_float_to_decimal(0.000002f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.000001f, 1e-9);
}
END_TEST

START_TEST(test_s21_float_sub_large_scale_difference) {
  // Test: s21_sub корректно вычитает два децимала, где один имеет больший scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(123456789, &a);
  s21_set_scale(&a, 6);
  s21_from_int_to_decimal(987, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 113.586789f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_negative_with_scale) {
  // Test: s21_sub корректно вычитает два децимала, где один имеет отрицательное
  // значение и больший масштаб
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(-12345, &a);
  s21_set_scale(&a, 3);
  s21_from_int_to_decimal(6789, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -80.235f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_precision_loss) {
  // Test: s21_sub корректно вычитает два децимала, с сохранением точности
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1.23456789f, &a);
  s21_from_float_to_decimal(0.00000001f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.23457f, 1e-5);
}
END_TEST

START_TEST(test_s21_float_sub_max_precision) {
  // Test: s21_sub корректно вычитает два децимала, где один имеет высокую
  // точность
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(100000000, &a);
  s21_set_scale(&a, 8);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 8);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.99999999f, 1e-8);
}
END_TEST

START_TEST(test_s21_float_sub_denormalized) {
  // Test: s21_sub корректно вычитает два децимала, приближенных к нулю
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(2, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 28);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_eq(s21_get_scale(result), 28);
  ck_assert_float_eq_tol(result_float, 1e-28f, 1e-30f);
}
END_TEST

START_TEST(test_s21_float_sub_borrow_across_bits) {
  // Test: s21_sub корректно занимает биты
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1.0f, &a);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 1);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.9f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_sub_large_negative_result) {
  // Test: s21_sub корректно вычитает два децимала, приближенных с малыми
  // значениями
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-1e+10f, &a);
  s21_from_float_to_decimal(1e+10f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -2e+10f, 1e+5f);
}
END_TEST

START_TEST(test_s21_float_sub_identical_numbers) {
  // Test: s21_sub корректно вычитает два одинаковых децимала
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(3.14159265f, &a);
  s21_from_float_to_decimal(3.14159265f, &b);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-8);
}
END_TEST

START_TEST(test_s21_float_sub_rounding_behavior) {
  // Test: s21_sub корректно округляет децималы
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(100000001, &a);
  s21_set_scale(&a, 8);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 9);
  s21_decimal result = {0};
  int outcome = s21_sub(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.00000000f, 1e-8);
}
END_TEST

START_TEST(test_s21_float_mul_positive) {
  // Test: s21_mul корректно умножает два децимала
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(2.5f, &a);
  s21_from_float_to_decimal(4.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 10.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_first_negative) {
  // Test: s21_mul корректно умножает два децимала, где первый отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-3.0f, &a);
  s21_from_float_to_decimal(2.5f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -7.5f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_second_negative) {
  // Test: s21_mul корректно умножает два децимала, где второй отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(3.0f, &a);
  s21_from_float_to_decimal(-2.5f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -7.5f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_both_negative) {
  // Test: s21_mul корректно умножает два децимала, где оба отрицательные
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-3.0f, &a);
  s21_from_float_to_decimal(-2.5f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 7.5f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_zero) {
  // Test: s21_mul корректно обрабатывает умножение на 0
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(42.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_zero_both) {
  // Test: s21_mul корректно обрабатывает умножение двух нолей
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_one) {
  // Test: s21_float_mul корректно обрабатывает умножение на 1
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(42.42f, &a);
  s21_from_float_to_decimal(1.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 42.42f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_different_scales) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с разными
  // scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(12.34f, &a);
  s21_from_float_to_decimal(5.678f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 70.06652f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_very_small_numbers) {
  // Test: s21_mul корректно обрабатывает умножение двух очень маленьких
  // децималов
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 14);
  s21_from_int_to_decimal(2, &b);
  s21_set_scale(&b, 14);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 2e-28f, 1e-30f);
}
END_TEST

START_TEST(test_s21_float_mul_large_scale_difference) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с большими
  // scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(123456789, &a);
  s21_set_scale(&a, 9);
  s21_from_int_to_decimal(987654321, &b);
  s21_set_scale(&b, 9);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.121932631, 1e-9);
}
END_TEST

START_TEST(test_s21_float_mul_negative_with_scale) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с различным
  // scale, где один отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(-1234567, &a);
  s21_set_scale(&a, 6);
  s21_from_int_to_decimal(7890123, &b);
  s21_set_scale(&b, 7);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -0.974089, 1e-6);
}
END_TEST

START_TEST(test_s21_float_mul_precision_limits) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с высокой
  // точностью
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(999999999, &a);
  s21_set_scale(&a, 9);
  s21_from_int_to_decimal(2, &b);
  s21_set_scale(&b, 0);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.999999998f, 1e-9);
}
END_TEST

START_TEST(test_s21_float_mul_scale_overflow) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с
  // переполнением scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 28);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_le(s21_get_scale(result), 28);
}
END_TEST

START_TEST(test_s21_float_mul_identical_numbers) {
  // Test: s21_mul корректно обрабатывает умножение двух одинаковых децималов
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(7.3f, &a);
  s21_from_float_to_decimal(7.3f, &b);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 53.29f, 1e-5);
}
END_TEST

START_TEST(test_s21_float_mul_max_scale) {
  // Test: s21_mul корректно обрабатывает умножение двух децималов с
  // максимальным scale
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(10, &b);
  s21_set_scale(&b, 0);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1e-27f, 1e-29f);
}
END_TEST

START_TEST(test_s21_float_mul_very_small_product) {
  // Test: s21_float_mul корректно обрабатывает умножение двух очень малых
  // децималов
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 14);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 14);
  s21_decimal result = {0};
  int outcome = s21_mul(a, b, &result);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_le(s21_get_scale(result), 28);
}
END_TEST

START_TEST(test_s21_float_div_positive) {
  // Test: s21_div корректно делит два децимала
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(10.0f, &a);
  s21_from_float_to_decimal(2.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 5.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_first_negative) {
  // Test: s21_div корректно делит два децимала, где первый отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-10.0f, &a);
  s21_from_float_to_decimal(2.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -5.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_second_negative) {
  // Test: s21_div корректно делит два децимала, где второй отрицательный
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(10.0f, &a);
  s21_from_float_to_decimal(-2.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -5.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_both_negative) {
  // Test: s21_div корректно делит два децимала, где оба отрицательные
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(-10.0f, &a);
  s21_from_float_to_decimal(-2.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 5.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_by_zero) {
  // Test: s21_div корректно делит децимал на ноль
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(10.0f, &a);
  s21_from_float_to_decimal(0.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 3);
}
END_TEST

START_TEST(test_s21_float_div_zero_by_number) {
  // Test: s21_div корректно делит ноль на децимал
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(0.0f, &a);
  s21_from_float_to_decimal(5.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_one) {
  // Test: s21_div корректно делит децимал на единицу
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(42.42f, &a);
  s21_from_float_to_decimal(1.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 42.42f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_different_scales) {
  // Test: s21_div корректно делит децималы с разными масштабами
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(92202, &a);
  s21_set_scale(&a, 3);
  s21_from_int_to_decimal(381, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 24.2, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_large_scale_difference) {
  // Test: s21_div корректно делит децималы с большим масштабом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(123456789, &a);
  s21_set_scale(&a, 9);
  s21_from_int_to_decimal(987654321, &b);
  s21_set_scale(&b, 9);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.125, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_negative_with_scale) {
  // Test: s21_div корректно делит отрицательный децимал на число с меньшим
  // масштабом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(-3000000, &a);
  s21_set_scale(&a, 5);
  s21_from_int_to_decimal(2000, &b);
  s21_set_scale(&b, 2);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -1.5, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_precision_limits) {
  // Test: s21_div корректно делит децималы с очень большим масштабом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(999999999, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(3, &b);
  s21_set_scale(&b, 0);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 3.33333333e-28f, 1e-10f);
}
END_TEST

START_TEST(test_s21_float_div_scale_management) {
  // Test: s21_div корректно управляет масштабом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 10);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 20);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_int_le(s21_get_scale(result), 28);
  ck_assert_float_eq_tol(result_float, 1e+10f, 1e+5f);
}
END_TEST

START_TEST(test_s21_float_div_large_numbers_small_result) {
  // Test: s21_div корректно делит децималы с очень большими числами
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1e+14f, &a);
  s21_from_float_to_decimal(1e+14f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_fractional_precision) {
  // Test: s21_div корректно отрабатывает дробную часть
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 0);
  s21_from_int_to_decimal(3, &b);
  s21_set_scale(&b, 0);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.333333333f, 1e-9);
}
END_TEST

START_TEST(test_s21_float_div_power_of_ten) {
  // Test: s21_div корректно делит децимал на степень десяти
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(123456.0f, &a);
  s21_from_float_to_decimal(1000.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 123.456f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_normalization_required) {
  // Test: s21_div корректно делит децималы с нормализацией
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(123456789, &a);
  s21_set_scale(&a, 5);
  s21_from_int_to_decimal(987654321, &b);
  s21_set_scale(&b, 5);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);

  ck_assert_int_eq(outcome, 0);

  float result_float;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_le(s21_get_scale(result), 28);
  ck_assert_float_eq_tol(result_float, 0.125, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_extreme_scale_values) {
  // Test: s21_div корректно делит два децимала с максимальным масштабом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_int_to_decimal(1, &a);
  s21_set_scale(&a, 28);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 28);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_periodic_fraction) {
  // Test: s21_div корректно делит децималы с периодической дробью
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1.0f, &a);
  s21_from_float_to_decimal(3.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 0.333333333f, 1e-9);
}
END_TEST

START_TEST(test_s21_float_div_by_one_minus_one) {
  // Test: s21_div корректно делит децимал на -1
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(42.0f, &a);
  s21_from_float_to_decimal(-1.0f, &b);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, -42.0f, 1e-6);
}
END_TEST

START_TEST(test_s21_float_div_very_large_result) {
  // Test: s21_div корректно делит децималы с огромным числом
  s21_decimal a = {{0}}, b = {{0}};
  s21_from_float_to_decimal(1e+14f, &a);
  s21_from_int_to_decimal(1, &b);
  s21_set_scale(&b, 14);
  s21_decimal result = {0};
  int outcome = s21_div(a, b, &result);
  float result_float;
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(outcome, 0);
  ck_assert_float_eq_tol(result_float, 1e+28f, 1e+25f);
}
END_TEST

START_TEST(test_s21_is_less_basic) {
  // Test: s21_is_less корректно сравнивает положительные числа
  s21_decimal a = {{10, 0, 0}};
  s21_decimal b = {{20, 0, 0}};
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(test_s21_is_less_negative) {
  // Test: s21_is_less корректно сравнивает отрицательные числа
  s21_decimal a = {{5, 0, 0}};
  s21_decimal b = {{10, 0, 0}};
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_s21_is_less_mixed_sign) {
  // Test: s21_is_less корректно сравнивает числа с разными знаками
  s21_decimal a = {{100, 0, 0}};
  s21_decimal b = {{50, 0, 0}};
  s21_set_sign(&b, 1);
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 2);

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_s21_is_less_equal_values) {
  // Test: s21_is_less корректно сравнивает равные значения
  s21_decimal a = {{123, 0, 0}};
  s21_decimal b = {{123, 0, 0}};
  s21_set_scale(&a, 2);  // 1.23
  s21_set_scale(&b, 2);  // 1.23

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(test_s21_is_less_different_scales) {
  // Test: s21_is_less корректно сравнивает числа с разными масштабами
  s21_decimal a = {{100, 0, 0}};
  s21_decimal b = {{10, 0, 0}};
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(test_s21_is_less_zero) {
  // Test: s21_is_less корректно сравнивает с нулем
  s21_decimal a = {{0, 0, 0}};
  s21_decimal b = {{5, 0, 0}};
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);

  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_basic) {
  // Test: s21_is_less_or_equal корректно сравнивает положительные числа
  s21_decimal a = {{15, 0, 0}};
  s21_decimal b = {{25, 0, 0}};
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_equal) {
  // Test: s21_is_less_or_equal корректно сравнивает одинаковые числа
  s21_decimal a = {{42, 0, 0}};
  s21_decimal b = {{42, 0, 0}};
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_basic) {
  // Test: s21_is_greater корректно сравнивает положительные
  s21_decimal a = {{30, 0, 0}};
  s21_decimal b = {{20, 0, 0}};
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);

  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
}
END_TEST

START_TEST(test_s21_is_greater_negative) {
  // Test: s21_is_greater корректно сравнивает отрицательные
  s21_decimal a = {0};
  s21_decimal b = {0};
  a.bits[0] = 1;
  b.bits[0] = 2;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_equal) {
  // Test: s21_is_greater_or_equal корректно сравнивает равные
  s21_decimal a = {{100, 0, 0}};
  s21_decimal b = {{100, 0, 0}};
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 2);

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_equal_basic) {
  // Test: s21_is_equal корректно сравнивает равные
  s21_decimal a = {{1234, 0, 0}};
  s21_decimal b = {{1234, 0, 0}};
  s21_set_scale(&a, 3);
  s21_set_scale(&b, 3);

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_equal_different_scale_same_value) {
  // Test: s21_is_equal корректно сравнивает равные с разным масштабом
  s21_decimal a = {{123, 0, 0}};
  s21_decimal b = {{1230, 0, 0}};
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 3);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_equal_different_sign) {
  // Test: s21_is_equal корректно сравнивает положительный и отрицательный ноль
  s21_decimal a = {{0, 0, 0}};
  s21_decimal b = {{0, 0, 0}};
  s21_set_sign(&a, 0);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_basic) {
  // Test: s21_is_not_equal корректно сравнивает разные числа
  s21_decimal a = {{1, 0, 0}};
  s21_decimal b = {{2, 0, 0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, a), 0);
}
END_TEST

START_TEST(test_s21_floor_positive) {
  // Test: s21_floor корректно округляет положительные
  s21_decimal val = {0};
  s21_from_float_to_decimal(3.7f, &val);
  s21_decimal result = {0};
  s21_floor(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, 3.0f);
}
END_TEST

START_TEST(test_s21_floor_negative) {
  // Test: s21_floor корректно округляет отрицательные
  s21_decimal val = {0};
  s21_from_float_to_decimal(-3.7f, &val);
  s21_decimal result = {0};
  s21_floor(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, -4.0f);
}
END_TEST

START_TEST(test_s21_round_up) {
  // Test: s21_floor корректно округляет вверх
  s21_decimal val = {0};
  s21_from_float_to_decimal(2.6f, &val);
  s21_decimal result = {0};
  s21_round(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, 3.0f);
}
END_TEST

START_TEST(test_s21_round_down) {
  // Test: s21_floor корректно округляет вниз
  s21_decimal val = {0};
  s21_from_float_to_decimal(2.4f, &val);
  s21_decimal result = {0};
  s21_round(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, 2.0f);
}
END_TEST

START_TEST(test_s21_round_negative_half_or_more) {
  // Test: s21_floor корректно округляет отрицательный вниз
  s21_decimal value = {{6, 0, 0, 0}};
  s21_set_scale(&value, 1);
  s21_set_sign(&value, 1);

  s21_decimal result = {0};

  s21_round(value, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, -1.0f);
}
END_TEST

START_TEST(test_s21_truncate_negative) {
  // Test: s21_truncate корректно отрезает нули
  s21_decimal val = {0};
  s21_from_float_to_decimal(-5.9f, &val);
  s21_decimal result = {0};
  s21_truncate(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, -5.0f);
}
END_TEST

START_TEST(test_s21_negate) {
  // Test: s21_negate корректно меняет знак
  s21_decimal val = {0};
  s21_from_float_to_decimal(42.0f, &val);
  s21_decimal result = {0};
  s21_negate(val, &result);
  float res_float;
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq(res_float, -42.0f);
}
END_TEST

START_TEST(test_s21_is_not_valid) {
  // Test: s21_is_not_valid корректно вычисляет невалидные децималы
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int outcome = s21_is_valid(a);

  ck_assert_int_eq(outcome, 0);
}
END_TEST

START_TEST(test_s21_bank_round_zero_scale) {
  // Test: s21_bank_round корректно обрабатывает 0 scale
  s21_decimal a = {{0x00000004, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_bank_round(a, &result);

  ck_assert_int_eq(result.bits[0], 4);
}
END_TEST

START_TEST(test_s21_bank_round_up) {
  // Тест: s21_bank_round корректно округляет вверх
  s21_decimal a = {{55, 0, 0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal result = {{0}};
  s21_bank_round(a, &result);

  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_bank_round_down) {
  // Тест: s21_bank_round корректно округляет вверх
  s21_decimal a = {{55, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_decimal result = {{0}};
  s21_bank_round(a, &result);

  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_s21_truncate_null) {
  // Тест: s21_truncate корректно обрабатывает ошибку аргумента
  s21_decimal a = {{55, 0, 0, 0}};
  int outcome = s21_truncate(a, NULL);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_increase_scale_overflow) {
  // Тест: s21_truncate корректно обрабатывает ошибку аргумента
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int outcome = s21_increase_scale(&a, 28);

  ck_assert_int_eq(outcome, 1);
}
END_TEST

START_TEST(test_s21_bank_round96_down) {
  // Тест: s21_bank_round96 корректно округляет вниз
  uint64_t temp[6] = {25, 0, 0, 0, 0, 0};
  int scale = 1;
  s21_bank_round96(temp, &scale);

  ck_assert_int_eq(scale, 0);
  ck_assert_int_eq(temp[0], 2);
}
END_TEST

START_TEST(test_s21_bank_round96_up) {
  // Тест: s21_bank_round96 корректно округляет вверх
  uint64_t temp[6] = {35, 0, 0, 0, 0, 0};
  int scale = 1;
  s21_bank_round96(temp, &scale);

  ck_assert_int_eq(scale, 0);
  ck_assert_int_eq(temp[0], 4);
}
END_TEST

SRunner *create_runner() {
  SRunner *sr;
  Suite *s21_transform;
  Suite *s21_arithmetic;
  Suite *s21_float_arithmetic;
  Suite *s21_comparison;
  Suite *s21_additional;
  TCase *tc_s21_from_decimal_to_int;
  TCase *tc_s21_from_int_to_decimal;
  TCase *tc_s21_from_float_to_decimal;
  TCase *tc_s21_from_decimal_to_float;
  TCase *tc_s21_add;
  TCase *tc_s21_sub;
  TCase *tc_s21_mul;
  TCase *tc_s21_div;
  TCase *tc_s21_fadd;
  TCase *tc_s21_fsub;
  TCase *tc_s21_fmul;
  TCase *tc_s21_fdiv;
  TCase *tc_s21_is_equal;
  TCase *tc_s21_is_less;
  TCase *tc_s21_is_greater;
  TCase *tc_s21_is_less_or_equal;
  TCase *tc_s21_is_greater_or_equal;
  TCase *tc_s21_is_not_equal;
  TCase *tc_s21_floor;
  TCase *tc_s21_round;
  TCase *tc_s21_truncate;
  TCase *tc_s21_negate;
  TCase *tc_s21_edge_cases;

  s21_transform = suite_create("transform");
  s21_arithmetic = suite_create("arithmetic");
  s21_float_arithmetic = suite_create("float_arithmetic");
  s21_comparison = suite_create("comparison");
  s21_additional = suite_create("additional");

  sr = srunner_create(s21_transform);
  srunner_add_suite(sr, s21_arithmetic);
  srunner_add_suite(sr, s21_float_arithmetic);
  srunner_add_suite(sr, s21_comparison);
  srunner_add_suite(sr, s21_additional);

  tc_s21_from_int_to_decimal = tcase_create("s21_from_int_to_decimal");
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_from_int_to_dec_base);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_from_negative_int);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_from_zero_int);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_max_int);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_min_int);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_itod_null_dst);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_one);
  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_minus_one);

  tc_s21_from_decimal_to_int = tcase_create("s21_from_decimal_to_int");
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_positive_decimal_to_int);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_negative_decimal_to_int);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_zero_decimal_to_int);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_max_int_to_decimal);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_min_int_to_decimal);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_overflow_positive);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_overflow_negative);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_dtoi_null_dst);
  tcase_add_test(tc_s21_from_decimal_to_int, test_s21_non_zero_high_bits);
  tcase_add_test(tc_s21_from_decimal_to_int,
                 test_s21_from_decimal_to_int_truncates_fractional_negative);
  tcase_add_test(tc_s21_from_decimal_to_int,
                 test_s21_from_decimal_to_int_truncates_fractional_positive);
  tcase_add_test(tc_s21_from_decimal_to_int,
                 test_s21_from_decimal_to_int_truncates_fractional_large);

  tc_s21_from_float_to_decimal = tcase_create("s21_from_float_to_decimal");
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_basic_positive);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_negative);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_zero);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_max_float);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_min_float);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_null_dst);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_one);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_minus_one);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_low_one);
  tcase_add_test(tc_s21_from_float_to_decimal, test_s21_ftod_trailing_zeros);

  tc_s21_from_decimal_to_float = tcase_create("s21_from_decimal_to_float");
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_basic_positive);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_negative);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_zero);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_large_number);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_small_number);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_null_dst);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_one);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_minus_one);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_precision);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_max_scale);
  tcase_add_test(tc_s21_from_decimal_to_float,
                 test_s21_dtof_within_float_precision);
  tcase_add_test(tc_s21_from_decimal_to_float, test_s21_dtof_large_with_scale);

  tc_s21_add = tcase_create("s21_add");
  tcase_add_test(tc_s21_add, test_s21_add_positive);
  tcase_add_test(tc_s21_add, test_s21_add_first_negative);
  tcase_add_test(tc_s21_add, test_s21_add_second_negative);
  tcase_add_test(tc_s21_add, test_s21_add_both_negative);
  tcase_add_test(tc_s21_add, test_s21_add_overflow_positive);
  tcase_add_test(tc_s21_add, test_s21_add_overflow_negative);
  tcase_add_test(tc_s21_add, test_s21_add_zero);
  tcase_add_test(tc_s21_add, test_s21_add_zero_first);
  tcase_add_test(tc_s21_add, test_s21_add_zero_second);
  tcase_add_test(tc_s21_add, test_s21_add_first_bit_overflow);
  tcase_add_test(tc_s21_add, test_s21_add_second_bit_overflow);
  tcase_add_test(tc_s21_add, test_s21_add_negative_large_numbers);
  tcase_add_test(tc_s21_add, test_s21_add_two_large_numbers);

  tc_s21_sub = tcase_create("s21_sub");
  tcase_add_test(tc_s21_sub, test_s21_sub_two_positive_numbers);
  tcase_add_test(tc_s21_sub, test_s21_sub_first_negative);
  tcase_add_test(tc_s21_sub, test_s21_sub_second_negative);
  tcase_add_test(tc_s21_sub, test_s21_sub_both_negative);
  tcase_add_test(tc_s21_sub, test_s21_sub_overflow_up);
  tcase_add_test(tc_s21_sub, test_s21_sub_overflow_down);
  tcase_add_test(tc_s21_sub, test_s21_sub_equal_numbers);
  tcase_add_test(tc_s21_sub, test_s21_sub_zero_from_positive);
  tcase_add_test(tc_s21_sub, test_s21_sub_zero_from_negative);
  tcase_add_test(tc_s21_sub, test_s21_sub_positive_from_zero);
  tcase_add_test(tc_s21_sub, test_s21_sub_negative_from_zero);

  tc_s21_mul = tcase_create("s21_mul");
  tcase_add_test(tc_s21_mul, test_s21_mul_two_positive_numbers);
  tcase_add_test(tc_s21_mul, test_s21_mul_first_negative);
  tcase_add_test(tc_s21_mul, test_s21_mul_second_negative);
  tcase_add_test(tc_s21_mul, test_s21_mul_both_negative);
  tcase_add_test(tc_s21_mul, test_s21_mul_with_zero);
  tcase_add_test(tc_s21_mul, test_s21_mul_by_one);
  tcase_add_test(tc_s21_mul, test_s21_mul_overflow_result);
  tcase_add_test(tc_s21_mul, test_s21_mul_underflow_result);

  tc_s21_div = tcase_create("s21_div");
  tcase_add_test(tc_s21_div, test_s21_div_basic);
  tcase_add_test(tc_s21_div, test_s21_div_neg_numerator);
  tcase_add_test(tc_s21_div, test_s21_div_neg_denominator);
  tcase_add_test(tc_s21_div, test_s21_div_both_neg);
  tcase_add_test(tc_s21_div, test_s21_div_zero_denominator);
  tcase_add_test(tc_s21_div, test_s21_div_zero_numerator);
  tcase_add_test(tc_s21_div, test_s21_div_one);

  tc_s21_fadd = tcase_create("s21_fadd");
  tcase_add_test(tc_s21_fadd, test_s21_float_add_positive);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_first_negative);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_second_negative);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_both_negative);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_overflow_positive);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_overflow_negative);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_zero);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_zero_first);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_zero_second);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_different_scales);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_very_small_numbers);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_large_scale_difference);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_negative_with_scale);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_precision_loss);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_max_precision);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_denormalized);
  tcase_add_test(tc_s21_fadd, test_s21_float_add_two_carrying);

  tc_s21_fsub = tcase_create("s21_fsub");
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_positive);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_first_negative);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_second_negative);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_both_negative);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_zero);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_zero_first);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_zero_second);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_different_scales);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_very_small_numbers);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_large_scale_difference);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_negative_with_scale);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_precision_loss);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_max_precision);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_denormalized);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_borrow_across_bits);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_large_negative_result);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_identical_numbers);
  tcase_add_test(tc_s21_fsub, test_s21_float_sub_rounding_behavior);

  tc_s21_fmul = tcase_create("s21_fmul");
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_positive);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_first_negative);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_second_negative);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_both_negative);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_zero);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_zero_both);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_one);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_different_scales);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_very_small_numbers);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_large_scale_difference);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_negative_with_scale);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_precision_limits);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_scale_overflow);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_identical_numbers);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_max_scale);
  tcase_add_test(tc_s21_fmul, test_s21_float_mul_very_small_product);

  tc_s21_fdiv = tcase_create("s21_fdiv");
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_positive);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_first_negative);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_second_negative);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_both_negative);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_by_zero);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_zero_by_number);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_one);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_different_scales);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_large_scale_difference);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_negative_with_scale);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_precision_limits);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_scale_management);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_large_numbers_small_result);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_fractional_precision);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_power_of_ten);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_normalization_required);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_extreme_scale_values);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_periodic_fraction);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_by_one_minus_one);
  tcase_add_test(tc_s21_fdiv, test_s21_float_div_very_large_result);

  tc_s21_is_less = tcase_create("s21_is_less");
  tcase_add_test(tc_s21_is_less, test_s21_is_less_basic);
  tcase_add_test(tc_s21_is_less, test_s21_is_less_negative);
  tcase_add_test(tc_s21_is_less, test_s21_is_less_mixed_sign);
  tcase_add_test(tc_s21_is_less, test_s21_is_less_equal_values);
  tcase_add_test(tc_s21_is_less, test_s21_is_less_different_scales);
  tcase_add_test(tc_s21_is_less, test_s21_is_less_zero);

  tc_s21_is_less_or_equal = tcase_create("s21_is_less_or_equal");
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal_basic);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal_equal);

  tc_s21_is_greater = tcase_create("s21_is_greater");
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater_basic);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater_negative);

  tc_s21_is_greater_or_equal = tcase_create("s21_is_greater_or_equal");
  tcase_add_test(tc_s21_is_greater_or_equal,
                 test_s21_is_greater_or_equal_equal);

  tc_s21_is_equal = tcase_create("s21_is_equal");
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal_basic);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal_different_scale_same_value);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal_different_sign);

  tc_s21_is_not_equal = tcase_create("s21_is_not_equal");
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal_basic);

  tc_s21_floor = tcase_create("s21_floor");
  tcase_add_test(tc_s21_floor, test_s21_floor_positive);
  tcase_add_test(tc_s21_floor, test_s21_floor_negative);

  tc_s21_round = tcase_create("s21_round");
  tcase_add_test(tc_s21_round, test_s21_round_up);
  tcase_add_test(tc_s21_round, test_s21_round_down);
  tcase_add_test(tc_s21_round, test_s21_round_negative_half_or_more);

  tc_s21_truncate = tcase_create("s21_truncate");
  tcase_add_test(tc_s21_truncate, test_s21_truncate_negative);

  tc_s21_negate = tcase_create("s21_negate");
  tcase_add_test(tc_s21_negate, test_s21_negate);

  tc_s21_edge_cases = tcase_create("s21_edge_cases");
  tcase_add_test(tc_s21_edge_cases, test_s21_is_not_valid);
  tcase_add_test(tc_s21_edge_cases, test_s21_bank_round_zero_scale);
  tcase_add_test(tc_s21_edge_cases, test_s21_bank_round_up);
  tcase_add_test(tc_s21_edge_cases, test_s21_bank_round_down);
  tcase_add_test(tc_s21_edge_cases, test_s21_truncate_null);
  tcase_add_test(tc_s21_edge_cases, test_s21_increase_scale_overflow);
  tcase_add_test(tc_s21_edge_cases, test_s21_bank_round96_down);
  tcase_add_test(tc_s21_edge_cases, test_s21_bank_round96_up);

  suite_add_tcase(s21_transform, tc_s21_from_int_to_decimal);
  suite_add_tcase(s21_transform, tc_s21_from_decimal_to_int);
  suite_add_tcase(s21_transform, tc_s21_from_float_to_decimal);
  suite_add_tcase(s21_transform, tc_s21_from_decimal_to_float);

  suite_add_tcase(s21_arithmetic, tc_s21_add);
  suite_add_tcase(s21_arithmetic, tc_s21_sub);
  suite_add_tcase(s21_arithmetic, tc_s21_mul);
  suite_add_tcase(s21_arithmetic, tc_s21_div);

  suite_add_tcase(s21_float_arithmetic, tc_s21_fadd);
  suite_add_tcase(s21_float_arithmetic, tc_s21_fsub);
  suite_add_tcase(s21_float_arithmetic, tc_s21_fmul);
  suite_add_tcase(s21_float_arithmetic, tc_s21_fdiv);

  suite_add_tcase(s21_comparison, tc_s21_is_less);
  suite_add_tcase(s21_comparison, tc_s21_is_less_or_equal);
  suite_add_tcase(s21_comparison, tc_s21_is_greater);
  suite_add_tcase(s21_comparison, tc_s21_is_greater_or_equal);
  suite_add_tcase(s21_comparison, tc_s21_is_equal);
  suite_add_tcase(s21_comparison, tc_s21_is_not_equal);

  suite_add_tcase(s21_additional, tc_s21_floor);
  suite_add_tcase(s21_additional, tc_s21_round);
  suite_add_tcase(s21_additional, tc_s21_truncate);
  suite_add_tcase(s21_additional, tc_s21_negate);
  suite_add_tcase(s21_additional, tc_s21_edge_cases);

  return sr;
}

int main() {
  SRunner *sr = create_runner();
  srunner_run_all(sr, CK_NORMAL);
  int failed_quantity = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_quantity == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
