#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

/*
** - Runner:
**   - Suite: String.a
***     - Testcase: s21_memchr
***       - Test: s21_memchr корректно отрабатывает
***       - Test: s21_memchr корректно отрабатывает с указателем на первый байт
***       - Test: s21_memchr корректно отрабатывает с указателем на последний
*байт
***       - Test: s21_memchr корректно отрабатывает с указателем вне зоны поиска
*(ошибка)
***       - Test: s21_memchr корректно отрабатывает с нуль-терминатором
***       - Test: s21_memchr корректно работает с простыми непечатаемыми
*символами
***       - Test: s21_memchr корректно отрабатывает с пустой строкой
***       - Test: s21_memchr корректно отрабатывает если чара нет в строке
***       - Test: s21_memchr корректно отрабатывает если длина строки больше n
***       - Test: s21_memchr корректно отрабатывает если длина строки меньше n и
*символ отсутствует
***       - Test: s21_memchr корректно отрабатывает если n = 0
***     - Testcase: s21_memcmp
***       - Test: s21_memcmp корректно отрабатывает с равными блоками
***       - Test: s21_memcmp корректно отрабатывает когда первый блок меньше
***       - Test: s21_memcmp корректно отрабатывает когда первый блок больше
***       - Test: s21_memcmp корректно отрабатывает когда разница в первым байте
***       - Test: s21_memcmp корректно отрабатывает когда разница в последнем
*байте
***       - Test: s21_memcmp корректно отрабатывает когда разница в середине
*строки
***       - Test: s21_memcmp корректно отрабатывает когда в середине строки есть
*нуль-терминатор
***       - Test: s21_memcmp корректно отрабатывает с непечатными символами
***       - Test: s21_memcmp корректно отрабатывает если первая строка пустая
***       - Test: s21_memcmp корректно отрабатывает если вторая строка пустая
***       - Test: s21_memcmp корректно отрабатывает если длина первой строки
*меньше n
***       - Test: s21_memcmp корректно отрабатывает если длина второй строки
*меньше n
***       - Test: s21_memcmp корректно отрабатывает если длина первой строки
*больше n
***       - Test: s21_memcmp корректно отрабатывает если длина второй строки
*больше n
***     - Testcase: s21_memcpy
***       - Test: s21_memcpy корректно отрабатывает с валидными данными
***       - Test: s21_memcpy корректно отрабатывает с массивами
***       - Test: s21_memcpy корректно отрабатывает с n = 0
***       - Test: s21_memcpy корректно отрабатывает с пустой строкой
***     - Testcase: s21_memset
***       - Test: s21_memset корректно отрабатывает заполнение массива символами
***       - Test: s21_memset корректно отрабатывает заполнение массива нулями
***       - Test: s21_memset корректно отрабатывает если n = 0
***       - Test: s21_memset корректно отрабатывает если n = 1
***       - Test: s21_memset корректно отрабатывает если n = размеру буффера
***       - Test: s21_memset корректно отрабатывает заполение нуль-терминатором
***       - Test: s21_memset корректно отрабатывает заполение непечатнвми
*символами
***       - Test: s21_memset корректно отрабатывает если n > размера буффера
***     - Testcase: s21_strncat
***       - Test: s21_strncat корректно отрабатывает полное добавление
***       - Test: s21_strncat корректно отрабатывает частичное добавление
***       - Test: s21_strncat корректно отрабатывает n = 0
***       - Test: s21_strncat корректно отрабатывает dest - пустая строка
***       - Test: s21_strncat корректно отрабатывает src - пустая строка
***       - Test: s21_strncat корректно отрабатывает если src меньше n
***       - Test: s21_strncat корректно отрабатывает если src больше n
***       - Test: s21_strncat корректно отрабатывает добавление нуль-терминатора
*через функцию
***       - Test: s21_strncat корректно отрабатывает непечатные символы
***     - Testcase: s21_strchr
***       - Test: s21_strchr корректно отрабатывает первый символ в строке
***       - Test: s21_strchr корректно отрабатывает последний символ в строке
***       - Test: s21_strchr корректно отрабатывает символ в середине строки
***       - Test: s21_strchr корректно отрабатывает с пустой строкой
***       - Test: s21_strchr корректно отрабатывает со строкой из одного символа
***       - Test: s21_strchr корректно отрабатывает поиск нуль-терминатора
***       - Test: s21_strchr корректно отрабатывает поиск непечатных символов
***       - Test: s21_strchr регистрозависима аналогично strchr
***       - Test: s21_strchr корректно отрабатывает поиск нуль-терминатора в
*пустой строке
***       - Test: s21_strchr корректно отрабатывает если символа отсутствует в
*строке
***       - Test: s21_strchr корректно отрабатывает множественные вхождения
***       - Test: s21_strchr корректно отрабатывает str = NULL (ошибка)
***     - Testcase: s21_strncmp
***       - Test: s21_strncmp корректно отрабатывает равные строки
***       - Test: s21_strncmp корректно отрабатывает случай, когда значение
*первой строки меньше
***       - Test: s21_strncmp корректно отрабатывает случай, когда значение
*первой строки больше
***       - Test: s21_strncmp корректно отрабатывает если длина первой строки
*больше второй
***       - Test: s21_strncmp корректно отрабатывает если длина второй строки
*больше первой
***       - Test: s21_strncmp корректно отрабатывает случай, когда n = 0
***       - Test: s21_strncmp корректно отрабатывает если длина первой строки
*меньше n
***       - Test: s21_strncmp корректно отрабатывает если длина второй строки
*меньше n
***       - Test: s21_strncmp корректно отрабатывает сравнение с
*нуль-терминатором
***       - Test: s21_strncmp корректно отрабатывает сравнение непечатных
*символов
***       - Test: s21_strncmp корректно отрабатывает пустые строки
***       - Test: s21_strncmp корректно отрабатывает первую пустую строку
***       - Test: s21_strncmp корректно отрабатывает вторую пустую строку
***       - Test: s21_strncmp корректно отрабатывает регистрозависимые строки
***     - Testcase: s21_strncpy
***       - Test: s21_strncpy корректно отрабатывает полное копирование
***       - Test: s21_strncpy корректно отрабатывает частичное копирование
***       - Test: s21_strncpy корректно отрабатывает случай, если n = 0
***       - Test: s21_strncpy корректно отрабатывает если src пустой
***       - Test: s21_strncpy корректно отрабатывает копирование
*нуль-терминатора
***       - Test: s21_strncpy корректно отрабатывает копирование непечатных
*символов
***       - Test: s21_strncpy корректно отрабатывает если dest пустой
***       - Test: s21_strncpy корректно отрабатывает если длина src меньше n
***       - Test: s21_strncpy корректно отрабатывает если длина src больше n
***       - Test: s21_strncpy корректно отрабатывает если src = null (ошибка)
***       - Test: s21_strncpy корректно отрабатывает если dest = null (ошибка)
***     - Testcase: s21_strcspn
***       - Test: s21_strcspn корректно отрабатывает случай, где ни один символ
*не встречается
***       - Test: s21_strcspn корректно отрабатывает случай, где первый символ
*содержится в str2
***       - Test: s21_strcspn корректно отрабатывает случай, где символ из str2
*находится в середине str1
***       - Test: s21_strcspn корректно отрабатывает случай, где str1 пустая
***       - Test: s21_strcspn корректно отрабатывает случай, где str2 пустая
***       - Test: s21_strcspn корректно отрабатывает случай, где обе строки
*пустые
***       - Test: s21_strcspn корректно отрабатывает поиск нуль-терминатора
***       - Test: s21_strcspn корректно отрабатывает поиск непечатных символов
***       - Test: s21_strcspn корректно отрабатывает случай, когда символ
*находится в конце str1
***       - Test: s21_strcspn корректно отрабатывает случай, когда совпадений
*несколько
***       - Test: s21_strcspn корректно отрабатывает регистрозависимость
***       - Test: s21_strcspn корректно отрабатывает дубликаты str2
***       - Test: s21_strcspn корректно отрабатывает случай, когда символы str2
*идут не лексикографически
***     - Testcase: s21_strerror
***        - Test: s21_strerror корректно отрабатывает обычное значение
***       - Test: s21_strerror корректно отрабатывает значение ошибки меньше
*ноля
***       - Test: s21_strerror корректно отрабатывает значение ошибки больше
*размера списка
***       - Test: s21_strerror корректно отрабатывает значение на границе списка
**     - Testcase: s21_strlen
***       - Test: s21_strlen корректно отрабатывает c валидной строкой
***       - Test: s21_strlen корректно отрабатывает с пустой строкой
***       - Test: s21_strlen корректно отрабатывает с пробелом
***       - Test: s21_strlen корректно отрабатывает с непечатными символами
***       - Test: s21_strlen корректно отрабатывает с нуль-терминатором в
*середине строки
***     - Testcase: s21_strpbrk
***       - Test: s21_strpbrk корректно отрабатывает совпадение в первом символе
***       - Test: s21_strpbrk корректно отрабатывает совпадение в середине
*строки
***       - Test: s21_strpbrk корректно отрабатывает совпадение в последнем
*символе
***       - Test: s21_strpbrk корректно отрабатывает совпадение с несколькими
*символами
***       - Test: s21_strpbrk корректно отрабатывает отсутствие совпадений
***       - Test: s21_strpbrk корректно отрабатывает если первая строка пустая
***       - Test: s21_strpbrk корректно отрабатывает если вторая строка пустая
***       - Test: s21_strpbrk корректно отрабатывает если обе строки пустые
***       - Test: s21_strpbrk корректно отрабатывает поиск спецсимволов
***       - Test: s21_strpbrk корректно отрабатывает поиск чисел
***       - Test: s21_strpbrk корректно отрабатывает регистрозависимость
***       - Test: s21_strpbrk корректно отрабатывает дублирующиеся символы в
*первой строке
***       - Test: s21_strpbrk корректно отрабатывает дублирующиеся символы во
*второй строке
***       - Test: s21_strpbrk корректно отрабатывает значения после
*нуль-терминатора
***       - Test: s21_strpbrk корректно отрабатывает совпадение с алфавитом
***       - Test: s21_strpbrk корректно отрабатывает совпадение с пробелом
***     - Testcase: s21_strrchr
***       - Test: s21_strrchr корректно отрабатывает единственное совпадение
***       - Test: s21_strrchr корректно отрабатывает множественное совпадение
***       - Test: s21_strrchr корректно отрабатывает совпадение в конце строки
***       - Test: s21_strrchr корректно отрабатывает совпадение в начале строки
***       - Test: s21_strrchr корректно отрабатывает отсутствие совпадений
***       - Test: s21_strrchr корректно отрабатывает пустую строку
***       - Test: s21_strrchr корректно отрабатывает поиск нуль-терминатора
***       - Test: s21_strrchr корректно отрабатывает поиск спецсимвола
***       - Test: s21_strrchr корректно отрабатывает регистрозависимость
***       - Test: s21_strrchr корректно отрабатывает поиск после
*нуль-терминатора
***       - Test: s21_strrchr корректно отрабатывает цифры в строке
***       - Test: s21_strrchr корректно отрабатывает пробел в строке
***     - Testcase: s21_strstr
***       - Test: s21_strstr корректно отрабатывает подстроку в начале
***       - Test: s21_strstr корректно отрабатывает подстроку в середине
***       - Test: s21_strstr корректно отрабатывает подстроку в конце
***       - Test: s21_strstr корректно отрабатывает совпадение строки и
*подстроки
***       - Test: s21_strstr корректно отрабатывает отсутствие совпадений
***       - Test: s21_strstr корректно отрабатывает если первая строка пустая
***       - Test: s21_strstr корректно отрабатывает если вторая строка пустая
***       - Test: s21_strstr корректно отрабатывает если обе строки пустые
***       - Test: s21_strstr корректно отрабатывает спецсимволы
***       - Test: s21_strstr корректно отрабатывает цифры
***       - Test: s21_strstr корректно отрабатывает регистрозависимость
***       - Test: s21_strstr корректно отрабатывает повторяющиеся символы
***       - Test: s21_strstr корректно отрабатывает перекрывающиеся подстроки
***       - Test: s21_strstr корректно отрабатывает частичные совпадения
***       - Test: s21_strstr корректно отрабатывает если длина подстроки больше
*строки
***       - Test: s21_strstr корректно отрабатывает строки с нуль-терминатором в
*середине
***       - Test: s21_strstr корректно отрабатывает подстроку в один символ
***       - Test: s21_strstr корректно отрабатывает пробел
***     - Testcase: s21_strtok
***       - Test: s21_strtok корректно отрабатывает простую токенизацию
***       - Test: s21_strtok корректно отрабатывает разные разделители
***       - Test: s21_strtok корректно отрабатывает пустую строку
***       - Test: s21_strtok корректно отрабатывает только разделители
***       - Test: s21_strtok корректно отрабатывает разделитель в начале
***       - Test: s21_strtok корректно отрабатывает разделитель в конце
***       - Test: s21_strtok корректно отрабатывает разделители с двух сторон
***       - Test: s21_strtok корректно отрабатывает регистрозависимость
***       - Test: s21_strtok корректно отрабатывает управляющие символы как
*разделители
***       - Test: s21_strtok корректно отрабатывает изменение разделителей между
*вызовами
***       - Test: s21_strtok корректно отрабатывает расширение набора
*разделителей
***       - Test: s21_strtok корректно отрабатывает разделитель цифру
***   - Suite: sprintf
***     - Testcase: main
***       - Test: c стандартный символ
***       - Test: c спецсимвол
***       - Test: c непечатный символ
***       - Test: d положительный
***       - Test: d отрицательный
***       - Test: d ноль
***       - Test: d инт_макс
***       - Test: d инт_мин
***       - Test: d и пробел (% d)
***       - Test: d и плюс (%+d)
***       - Test: d + width - форматирование по ширине (%3d)
***       - Test: d + width + флаг - - форматирование по ширине (%-3d)
***       - Test: f обычное значение
***       - Test: f 0.0
***       - Test: f -0.0
***       - Test: f + precision - форматирование по точности (%2f)
***       - Test: f + precision - форматирование по точности и ширине (%10.3f)
***       - Test: s базовый случай
***       - Test: s пустая строка
***       - Test: s null
***       - Test: s + width                (%.3s)
***       - Test: s + precision            (%10s)
***       - Test: u Стандартное значение
***       - Test: u 0
***       - Test: u UINT_MAX
***       - Test: u -1
***       - Test: % одиночный
***       - Test: % в комбинации (100%%)
***       - Test: i положительный
***       - Test: i отрицательный
***       - Test: i ноль
***       - Test: i инт_макс
***       - Test: i инт_мин
***       - Test: i + width - форматирование по ширине (%3d)
***       - Test: i + width - форматирование по ширине (%-3d)
***       - Test: i шестнадцатиричное
***       - Test: i восьмиричное
***       - Test: ширина для %с
***       - Test: точность 0 для %d
***       - Test: точность для %u
***       - Test: %hd для short int
***       - Test: %ld для long int
***       - Test: %lf для long float
***       - Test: все модификаторы %#-+4.5ld"
***       - Test: разные спецификаторы в строке %c %d %f %s
***       - Test: incorrect specifier
***     - Testcase: bonus
***       - Test: # для float
***       - Test: n подсчет символов
***       - Test: n комбинация с %d
***       - Test: %X
***       - Test: %x
***       - Test: %g
***       - Test: s + precision            (%*s)(бонус)
***       - Test: d + width - форматирование по ширине (%*d) (бонус)
***       - Test: f + precision - форматирование по точности (%.*f)   (бонус)
***       - Test: f + width - форматирование по точности и ширине (%*.*f)
*(бонус)
***       - Test: s + width                (%.*s) (бонус)
***       - Test: i + width - форматирование по ширине (%*d) (бонус)
***       - Test: отрицательная ширина со звездой с %d (%*d, -5, 10) (бонус)
***       - Test: %o (бонус)
***       - Test: %p (бонус)
***       - Test: #x (бонус)
***       - Test: #o (бонус)
***       - Test: #g (бонус)
***       - Test: %Lf (бонус)
***       - Test: %Le (бонус)
***       - Test: %LE (бонус)
***       - Test: %Lg (бонус)
***       - Test: %Lf на INFINITY (бонус)
***       - Test: %Lf на -INFINITY (бонус)
***       - Test: %Lf на NAN (бонус)
***   - Suite: scanf
***     - Testcase: main
***       - Test: c стандартный символ
***       - Test: c спецсимвол
***       - Test: c непечатный символ
***       - Test: вывод = NULL
***       - Test: d положительный
***       - Test: d отрицательный
***       - Test: d ноль
***       - Test: d инт_макс
***       - Test: d инт_мин
***       - Test: d и пробел (%+ d)
***       - Test: d + width - форматирование по ширине (%3d)
***       - Test: f обычное значение
***       - Test: f 0.0
***       - Test: f -0.0
***       - Test: f inf
***       - Test: f + width - форматирование по ширине (%2f)
***       - Test: s базовый случай
***       - Test: s пустая строка
**       - Test: u Стандартное значение
**       - Test: u 0
**       - Test: % одиночный
**       - Test: % в комбинации (100%%)
**       - Test: i положительный
**       - Test: i отрицательный
**       - Test: i ноль
**       - Test: i инт_макс
**       - Test: i инт_мин
**       - Test: i + width - форматирование по ширине (%3d)
**       - Test: n подсчет символов
**       - Test: n комбинация с %d
**       - Test: ширина для %с
**       - Test: %hd для short int
**       - Test: %ld для long int
**       - Test: %lf для long float
**       - Test: %X
**       - Test: %x
**       - Test: %g
**       - Test: разные спецификаторы в строке %d %f %s
**       - Test: %*d - подавление присваивания
**       - Test: %*f - подавление присваивания
**       - Test: %*s - подавление присваивания
**       - Test: i + width - форматирование по ширине (%*d)
**       - Test: %o
**       - Test: %p
**       - Test: %Lf
**       - Test: %Le
**       - Test: %LE
**       - Test: %Lg
**       - Test: %Lf на INFINITY
**       - Test: %Lf на -INFINITY
**       - Test: %Lf на NAN
*   - Suite: additional_functions
**     - Testcase: s21_to_upper
**       - Test: Функция отрабатывает корректно на обычной строке
**       - Test: Функция отрабатывает корректно на строке с заглавными буквами
**       - Test: Функция отрабатывает корректно на пустой строке
**       - Test: Функция отрабатывает корректно на строке с цифрами и символами
**       - Test: Функция отрабатывает корректно при строке = NULL
**     - Testcase: s21_to_lower
**       - Test: Функция отрабатывает корректно на обычной строке
**       - Test: Функция отрабатывает корректно на строке со строчными буквами
**       - Test: Функция отрабатывает корректно на пустой строке
**       - Test: Функция отрабатывает корректно на строке с цифрами и символами
**       - Test: Функция отрабатывает корректно при строке = NULL
**     - Testcase: s21_insert
**       - Test: Функция отрабатывает корректно с обычной вставкой
**       - Test: Функция отрабатывает корректно со вставкой пустой строки в
*обычную строку
**       - Test: Функция отрабатывает корректно со вставкой обычной строки в
*пустую строку
**       - Test: Функция отрабатывает корректно со вставкой обычной строки в
*начало строки
**       - Test: Функция отрабатывает корректно со вставкой обычной строки в
*конец строки
**       - Test: Функция отрабатывает корректно со вставкой обычной строки за
*границы массива
**       - Test: Функция отрабатывает корректно со вставкой строки в NULL
**       - Test: Функция отрабатывает корректно со вставкой NULL в строку
**     - Testcase: s21_trim
**       - Test: Функция отрабатывает корректно с пробелом
**       - Test: Функция отрабатывает корректно c несколькими повторяющимися
*символами
**       - Test: Функция отрабатывает корректно c несколькими разными символами
**       - Test: Функция отрабатывает корректно без совпадений
**       - Test: Функция отрабатывает корректно если строка состоит из символов
*для обрезки
**       - Test: Функция отрабатывает корректно с пустой строкой
**       - Test: Функция отрабатывает корректно с пустым trim
**       - Test: Функция отрабатывает корректно с trim = NULL
**       - Test: Функция отрабатывает корректно со строкой = NULL
**       - Test: Функция отрабатывает корректно с совпадениями только в начале
**       - Test: Функция отрабатывает корректно с совпадениями только в конце
**       - Test: Функция отрабатывает корректно с совпадениями посередине
*/

START_TEST(test_s21_memchr_correct) {
  // Тест: s21_memchr корректно работает с валидными данными
  char str[] = "s21_string.h";
  int ch = 'n';
  s21_size_t n = strlen(str);
  char *expected = memchr(str, ch, n);
  char *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memchr_fb) {
  // Test: s21_memchr корректно отрабатывает с указателем на первый байт
  char str[] = "s21_string";
  int ch = 's';
  s21_size_t n = strlen(str);
  void *expected = memchr(str, ch, n);
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memchr_lb) {
  // Test: s21_memchr корректно отрабатывает с указателем на последний байт
  char str[] = "s21_string";
  int ch = 'g';
  s21_size_t n = strlen(str);
  void *expected = memchr(str, ch, n);
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memchr_out_of_reach) {
  // Test: s21_memchr корректно отрабатывает с указателем вне зоны поиска
  char str[] = "s21_string";
  int ch = 'g';
  s21_size_t n = 5;
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, NULL);
}
END_TEST

START_TEST(test_s21_memchr_null_term) {
  // Test: s21_memchr корректно отрабатывает с нуль-терминатором
  char str[] = "s21_\0string";
  int ch = '\0';
  s21_size_t n = sizeof(str);
  void *expected = memchr(str, ch, n);
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memchr_invis) {
  // Test: s21_memchr корректно работает с простыми непечатаемыми символами
  char str[] = "s21_\tstring";
  s21_size_t n = strlen(str);
  void *expected_tab = memchr(str, '\t', n);
  void *actual_tab = s21_memchr(str, '\t', n);

  ck_assert_ptr_eq(actual_tab, expected_tab);
}
END_TEST

START_TEST(test_s21_memchr_empty_str) {
  // Test: s21_memchr корректно отрабатывает с пустой строкой
  char empty_str[] = "";
  int ch = 's';
  s21_size_t n = 0;
  void *actual = s21_memchr(empty_str, ch, n);

  ck_assert_ptr_eq(actual, NULL);
}
END_TEST

START_TEST(test_s21_memchr_char_not_exist) {
  // Test: s21_memchr корректно отрабатывает если чара нет в строке
  char str[] = "s21_string";
  int ch = 'z';
  s21_size_t n = strlen(str);
  void *expected = memchr(str, ch, n);
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);  // Ожидаем NULL
}
END_TEST

START_TEST(test_s21_memchr_n_eq_zero) {
  // Test: s21_memchr корректно отрабатывает если n = 0
  char str[] = "s21_string";
  int ch = 's';
  void *result = s21_memchr(str, ch, 0);

  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_memchr_len_greater_than_n) {
  // Test: s21_memchr корректно отрабатывает если длина строки больше n
  char str[] = "s21_string";
  int ch = 'i';
  s21_size_t n = 5;
  void *expected = memchr(str, ch, n);
  void *actual = s21_memchr(str, ch, n);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcmp_equal) {
  // Test: s21_memcmp корректно отрабатывает с равными блоками
  char str1[] = "s21_string";
  char str2[] = "s21_string";
  s21_size_t n = strlen(str1);
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcmp_fb_greater) {
  // Test: s21_memcmp корректно отрабатывает когда первая строка длиннее
  char str1[] = "s21_string";
  char str2[] = "s21_str";
  s21_size_t n = 8;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual > 0, expected > 0);
}
END_TEST

START_TEST(test_s21_memcmp_fb_less) {
  // Test: s21_memcmp корректно отрабатывает когда первый блок короче
  char str1[] = "s21_str";
  char str2[] = "s21_string";
  s21_size_t n = 8;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual < 0, expected < 0);
}
END_TEST

START_TEST(test_s21_memcmp_fbite) {
  // Test: s21_memcmp корректно отрабатывает когда разница в первом байте
  char str1[] = "s21_string";
  char str2[] = "t21_string";
  s21_size_t n = strlen(str1);
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual < 0, expected < 0);
}
END_TEST

START_TEST(test_s21_memcmp_lbite) {
  // Test: s21_memcmp корректно отрабатывает когда разница в последнем байте
  char str1[] = "s21_string";
  char str2[] = "s21_strinh";
  s21_size_t n = strlen(str1);
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual < 0, expected < 0);
}
END_TEST

START_TEST(test_s21_memcmp_middle) {
  // Test: s21_memcmp корректно отрабатывает когда разница в середине строки
  char str1[] = "s21_string";
  char str2[] = "s21-string";
  s21_size_t n = strlen(str1);
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual > 0, expected > 0);
}
END_TEST

START_TEST(test_s21_memcmp_null_term) {
  // Test: s21_memcmp корректно отрабатывает когда в середине строки есть
  // нуль-терминатор
  char str1[] = "s21_\0string";
  char str2[] = "s21_\0STRING";
  s21_size_t n = 11;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual > 0, expected > 0);
}
END_TEST

START_TEST(test_s21_memcmp_invis) {
  // Test: s21_memcmp корректно отрабатывает с непечатными символами
  char str1[] = "s21_\tstring";
  char str2[] = "s21_\tstring";
  s21_size_t n = 11;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcmp_f_empty_str) {
  // Test: s21_memcmp корректно отрабатывает если первая строка пустая
  char str1[] = "";
  char str2[] = "s21_string";
  s21_size_t n = 1;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual,
                   expected);  // Пустая строка считается меньше непустой
}
END_TEST

START_TEST(test_s21_memcmp_s_empty_str) {
  // Test: s21_memcmp корректно отрабатывает если вторая строка пустая
  char str1[] = "s21_string";
  char str2[] = "";
  s21_size_t n = 1;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcmp_fs_less_than_n) {
  // Test: s21_memcmp корректно отрабатывает если длина первой строки меньше n
  char str1[] = "s21_str";
  char str2[] = "s21_string";
  s21_size_t n = 8;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual < 0, expected < 0);
}
END_TEST

START_TEST(test_s21_memcmp_ss_less_than_n) {
  // Test: s21_memcmp корректно отрабатывает если длина второй строки меньше n
  char str1[] = "s21_string";
  char str2[] = "s21_str";
  s21_size_t n = 8;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual > 0, expected > 0);
}
END_TEST

START_TEST(test_s21_memcmp_fs_greater_than_n) {
  // Test: s21_memcmp корректно отрабатывает если длина первой строки больше n
  char str1[] = "s21_string";
  char str2[] = "s21_str";
  s21_size_t n = 7;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcmp_ss_greater_than_n) {
  // Test: s21_memcmp корректно отрабатывает если длина второй строки больше n
  char str1[] = "s21_str";
  char str2[] = "s21_string";
  s21_size_t n = 7;
  int actual = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_memcpy_correct) {
  // Test: s21_memcpy корректно отрабатывает с валидными данными
  char src[] = "s21_string";
  char dest_std[20] = {0};
  char dest_s21[20] = {0};
  s21_size_t n = strlen(src) + 1;
  memcpy(dest_std, src, n);
  s21_memcpy(dest_s21, src, n);

  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, n), dest_s21);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_memcpy_arrs) {
  // Test: s21_memcpy корректно отрабатывает с массивами
  int src_int[] = {10, 20, 30, 40, 50};
  int dest_int_std[5] = {0};
  int dest_int_s21[5] = {0};
  s21_size_t int_size = sizeof(src_int);
  memcpy(dest_int_std, src_int, int_size);
  s21_memcpy(dest_int_s21, src_int, int_size);

  ck_assert_mem_eq(dest_int_s21, dest_int_std, int_size);
}
END_TEST

START_TEST(test_s21_memcpy_n_eq_null) {
  // Test: s21_memcpy корректно отрабатывает с n = 0 (ничего не копирует)
  char src[] = "";
  char dest_std[15] = "s21_string";
  char dest_s21[15] = "s21_string";
  s21_size_t n = 0;
  memcpy(dest_std, src, n);
  s21_memcpy(dest_s21, src, n);

  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_memcpy_empty_str) {
  // Test: s21_memcpy корректно отрабатывает с пустой строкой
  char src[] = "";
  char dest_std[15] = "s21_string";
  char dest_s21[15] = "s21_string";
  s21_size_t n = sizeof(src);
  memcpy(dest_std, src, n);
  s21_memcpy(dest_s21, src, n);

  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_memset_basic) {
  // Test: s21_memset корректно отрабатывает заполнение массива символами
  char string[15] = "s21_string";
  const char expected[15] = "xxx_string";
  void *actual = s21_memset(string, 'x', 3);

  ck_assert_ptr_eq(actual, string);
  ck_assert_str_eq(string, expected);
}
END_TEST

START_TEST(test_s21_memset_array_null) {
  // Test: s21_memset корректно отрабатывает заполнение массива нулями
  char string[15] = "s21_string";
  void *actual = s21_memset(string, '0', 10);

  ck_assert_str_eq(string, "0000000000");
  ck_assert_ptr_eq(actual, string);
}
END_TEST

START_TEST(test_s21_memset_n_eq_zero) {
  // Test: s21_memset корректно отрабатывает если n = 0
  char buffer[15] = "s21_string";
  const char original[15] = "s21_string";
  void *actual = s21_memset(buffer, 'X', 0);

  ck_assert_ptr_eq(actual, buffer);
  ck_assert_str_eq(buffer, original);
}
END_TEST

START_TEST(test_s21_memset_n_eq_one) {
  // Test: s21_memset корректно отрабатывает если n = 1
  char buffer[15] = "s21_string";
  const char expected[15] = "x21_string";
  void *actual = s21_memset(buffer, 'x', 1);

  ck_assert_ptr_eq(actual, buffer);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_memset_n_eq_buff) {
  // Test: s21_memset корректно отрабатывает если n = размеру буфера
  char buffer[11] = "s21_string";
  const s21_size_t buffer_size = sizeof(buffer);
  void *actual = s21_memset(buffer, 'x', buffer_size);

  ck_assert_ptr_eq(actual, buffer);
}
END_TEST

START_TEST(test_s21_memset_null_term) {
  // Test: s21_memset корректно отрабатывает заполение нуль-терминатором
  char buffer[11] = "s21_string";
  s21_memset(buffer, '\0', sizeof(buffer));

  for (s21_size_t i = 0; i < sizeof(buffer); i++) {
    ck_assert_int_eq(buffer[i], '\0');
  }
}
END_TEST

START_TEST(test_s21_memset_invis) {
  // Test: s21_memset корректно отрабатывает заполение непечатнвми символами
  char buffer[11] = "s21_string";
  s21_memset(buffer, '\n', 3);
  s21_memset(buffer + 3, '\t', 2);

  ck_assert_int_eq(buffer[2], '\n');
  ck_assert_int_eq(buffer[4], '\t');
  ck_assert_int_eq(buffer[5], 't');
}
END_TEST

START_TEST(test_s21_memset_n_gt_buff) {
  // Test: s21_memset корректно отрабатывает если n > размера буффера
  char buffer[10] = {0};
  char expected[10] = {0};
  int c = 'A';
  s21_size_t n = 15;
  memset(expected, c, sizeof(buffer));
  void *actual = s21_memset(buffer, c, n);

  ck_assert_ptr_eq(actual, buffer);
  ck_assert_mem_eq(buffer, expected, sizeof(buffer));
}
END_TEST

START_TEST(test_s21_strncat_correct_full) {
  // Test: s21_strncat корректно отрабатывает полное добавление
  char dest[20] = "s21_";
  const char *src = "string";
  s21_size_t n = strlen(src);
  char *actual = s21_strncat(dest, src, n);

  ck_assert_str_eq(dest, "s21_string");
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncat_correct_part) {
  // Test: s21_strncat корректно отрабатывает частичное добавление
  char dest[20] = "s21_";
  const char *src = "string";
  s21_size_t n = 3;
  const char *expected = "s21_str";
  char *actual = s21_strncat(dest, src, n);

  // Assert
  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncat_n_eq_zero) {
  // Test: s21_strncat корректно отрабатывает n = 0
  char dest[20] = "s21_";
  const char *src = "string";
  s21_size_t n = 0;
  char original_dest[20] = {0};
  strcpy(original_dest, dest);
  char *actual = s21_strncat(dest, src, n);

  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  // Test: s21_strncat корректно отрабатывает src - пустая строка
  char dest[20] = "s21_string";
  const char *src = "";
  s21_size_t n = 5;
  char original_dest[20] = {0};
  strcpy(original_dest, dest);
  char *actual = s21_strncat(dest, src, n);

  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  // Test: s21_strncat корректно отрабатывает dest - пустая строка
  char dest[20] = "";
  const char *src = "s21_string";
  s21_size_t n = strlen(src);
  char *actual = s21_strncat(dest, src, n);

  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, src);
  ck_assert_int_eq(strlen(dest), n);
  ck_assert_int_eq(dest[n], '\0');
}
END_TEST

START_TEST(test_s21_strncat_src_less_than_n) {
  // Test: s21_strncat корректно отрабатывает если src меньше n
  char dest[20] = "s21_";
  const char *src = "string";
  s21_size_t src_len = strlen(src);
  s21_size_t n = src_len + 2;
  char expected[20] = {0};
  strcpy(expected, dest);
  strncat(expected, src, n);
  char *actual = s21_strncat(dest, src, n);

  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, expected);
  ck_assert_int_eq(strlen(dest), strlen(expected));
}
END_TEST

START_TEST(test_s21_strncat_src_greater_than_n) {
  // Test: s21_strncat корректно отрабатывает если src больше n
  char dest[20] = "s21_";
  const char *src = "string";
  s21_size_t n = 3;
  const char *expected = "s21_str";
  char *actual = s21_strncat(dest, src, n);

  ck_assert_str_eq(actual, expected);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncat_src_null_term_add) {
  // Test: s21_strncat корректно отрабатывает добавление нуль-терминатора
  char dest[20] = "s21_";
  const char src[] = {'s', 't', 'r', 'i', 'n', 'g'};
  s21_size_t n = sizeof(src);
  const char *expected = "s21_string";
  char *actual = s21_strncat(dest, src, n);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(strlen(actual), strlen("s21_") + n);
  ck_assert(dest[strlen("s21_") + n] == '\0');
}
END_TEST

START_TEST(test_s21_strncat_invis) {
  // Test: s21_strncat корректно отрабатывает непечатные символы
  char dest_act[20] = "s21_";
  char dest_exp[20] = "s21_";
  const char *src = "\tstr\ning";
  s21_size_t n = s21_strlen(src);
  strncat(dest_exp, src, n);
  char *actual = s21_strncat(dest_act, src, n);

  ck_assert_ptr_eq(actual, dest_act);
  ck_assert_str_eq(dest_exp, dest_act);
  ck_assert_int_eq(dest_act[4], '\t');
  ck_assert_int_eq(dest_act[8], '\n');
  ck_assert_int_eq(dest_act[12], '\0');
}
END_TEST

START_TEST(test_s21_strchr_correct_fs) {
  // Test: s21_strchr корректно отрабатывает первый символ в строке
  const char *str = "s21_string";
  int c = 's';
  const char *expected = str;
  const char *actual = s21_strchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, c);
}
END_TEST

START_TEST(test_s21_strchr_correct_ls) {
  // Test: s21_strchr корректно отрабатывает последний символ в строке
  const char *str = "s21_string";
  int c = 'g';
  const char *expected = str + strlen(str) - 1;
  const char *actual = s21_strchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, c);
}
END_TEST

START_TEST(test_s21_strchr_correct_middle) {
  // Test: s21_strchr корректно отрабатывает символ в середине строки
  const char *str = "s21_string";
  int c = '_';
  const char *expected = str + 3;
  const char *actual = s21_strchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, c);
}
END_TEST

START_TEST(test_s21_strchr_empty_str) {
  // Test: s21_strchr корректно отрабатывает с пустой строкой
  const char *str = "";
  const char *actual = s21_strchr(str, 'a');

  ck_assert_ptr_null(actual);
}

START_TEST(test_s21_strchr_single_char) {
  // Test: s21_strchr корректно отрабатывает со строкой из одного символа
  const char *str = "s";
  const char *expected = str;
  const char *actual = s21_strchr(str, 's');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 's');
}
END_TEST

START_TEST(test_s21_strchr_null_search) {
  // Test: s21_strchr корректно отрабатывает поиск нуль-терминатора в середине
  // строки
  char str_with_null[15] = "s21\0_string";
  const char *expected = str_with_null + 3;
  const char *actual = s21_strchr(str_with_null, '\0');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, '\0');
}
END_TEST

START_TEST(test_s21_strchr_invis) {
  // Test: s21_strchr корректно отрабатывает поиск непечатных символов
  const char *str = "s21_\n\tstring\n";
  const char *actual;

  actual = s21_strchr(str, '\n');
  ck_assert_ptr_eq(actual, str + 4);

  actual = s21_strchr(str, '\t');
  ck_assert_ptr_eq(actual, str + 5);
}
END_TEST

START_TEST(test_s21_strchr_registr) {
  // Test: s21_strchr регистрозависима аналогично strchr
  const char *str = "s21_String";
  const char *lower_case = "s";
  const char *upper_case = "S";
  const char *s21_actual_lower = s21_strchr(str, *lower_case);
  const char *s21_actual_upper = s21_strchr(str, *upper_case);
  const char *actual_lower = strchr(str, *lower_case);
  const char *actual_upper = strchr(str, *upper_case);

  ck_assert_ptr_eq(s21_actual_lower, actual_lower);
  ck_assert_ptr_eq(s21_actual_upper, actual_upper);
}
END_TEST

START_TEST(test_s21_strchr_null_term_empty_str) {
  // Test: s21_strchr корректно отрабатывает поиск нуль-терминатора в пустой
  // строке
  const char *empty_str = "";
  const char *expected = empty_str;
  const char *actual = s21_strchr(empty_str, '\0');

  ck_assert_ptr_nonnull(actual);
  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strchr_symb_not_exist) {
  // Test: s21_strchr корректно отрабатывает если символ отсутствует в строке
  const char *str = "s21_string";
  const char *actual = s21_strchr(str, 'a');

  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strchr_mult_entry) {
  // Test: s21_strchr корректно отрабатывает множественные вхождения
  const char *str = "s21_string";
  const char *expected = str;
  const char *actual = s21_strchr(str, 's');

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strchr_null_str) {
  // Test: s21_strchr корректно отрабатывает str = NULL
  const char *str = NULL;
  const char *actual = s21_strchr(str, 's');

  ck_assert_ptr_eq(actual, NULL);
}
END_TEST

START_TEST(test_s21_strncmp_eq) {
  // Test: s21_strncmp корректно отрабатывает равные строки
  const char *str1 = "s21_string";
  const char *str2 = "s21_string";
  s21_size_t n = strlen(str1);
  int actual = s21_strncmp(str1, str2, n);

  ck_assert_int_eq(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_second_string_greater) {
  // Test: s21_strncmp корректно отрабатывает случай, когда значение первой
  // строки меньше
  const char *lower_str = "s21_string";
  const char *higher_str = "t21_string";
  s21_size_t n = 5;
  int actual = s21_strncmp(lower_str, higher_str, n);

  ck_assert_int_lt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_first_string_greater) {
  // Test: s21_strncmp корректно отрабатывает случай, когда значение первой
  // строки больше
  const char *lower_str = "s21_string";
  const char *higher_str = "t21_string";
  s21_size_t n = 5;
  int actual = s21_strncmp(higher_str, lower_str, n);

  ck_assert_int_gt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_second_string_length_greater) {
  // Test: s21_strncmp корректно отрабатывает если длина второй строки больше
  // первой
  const char *short_str = "s21";
  const char *long_str = "s21_string";
  s21_size_t n = strlen(long_str);
  int actual = s21_strncmp(short_str, long_str, n);

  ck_assert_int_lt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_first_string_length_greater) {
  // Test: s21_strncmp корректно отрабатывает если длина первой строки больше
  // второй
  const char *short_str = "s21";
  const char *long_str = "s21_string";
  s21_size_t n = strlen(long_str);
  int actual = s21_strncmp(long_str, short_str, n);

  ck_assert_int_gt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_n_eq_zero) {
  // Test: s21_strncmp корректно отрабатывает случай, когда n = 0
  const char *str1 = "s21_string";
  const char *str2 = "s21_string";
  s21_size_t n = 0;
  int actual = s21_strncmp(str1, str2, n);

  ck_assert_int_eq(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_null_term) {
  // Test: s21_strncmp корректно отрабатывает сравнение с нуль-терминатором
  char str_with_null[15] = "s21_\0string";
  const char *normal_str = "s21_";
  s21_size_t n = 8;
  int actual = s21_strncmp(str_with_null, normal_str, n);

  ck_assert_int_eq(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_invis) {
  // Test: s21_strncmp корректно обрабатывает символ табуляции
  const char *str1 = "s21_\tstring";
  const char *str2 = "s21_\tstring";
  s21_size_t n = 15;
  int actual = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);

  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strncmp_both_empty) {
  // Test: s21_strncmp корректно отрабатывает пустые строки
  const char *empty = "";
  const char *string = "";
  s21_size_t n = 0;
  int actual = s21_strncmp(empty, string, n);

  ck_assert_int_eq(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_first_string_empty) {
  // Test: s21_strncmp корректно отрабатывает если первая строка пустая
  const char *empty = "";
  const char *string = "s21_string";
  s21_size_t n = 1;
  int actual = s21_strncmp(empty, string, n);

  ck_assert_int_lt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_second_string_empty) {
  // Test: s21_strncmp корректно отрабатывает если вторая строка пустая
  const char *string = "s21_string";
  const char *empty = "";
  s21_size_t n = 1;
  int actual = s21_strncmp(string, empty, n);

  ck_assert_int_gt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_first_string_less_than_n) {
  // Test: s21_strncmp корректно отрабатывает если длина первой строки меньше n
  const char *short_str = "s21";
  const char *long_str = "s21_string";
  s21_size_t n = 5;
  int actual = s21_strncmp(short_str, long_str, n);

  ck_assert_int_lt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_second_string_less_than_n) {
  // Test: s21_strncmp корректно отрабатывает если длина второй строки меньше n
  const char *long_str = "s21_string";
  const char *short_str = "s21";
  s21_size_t n = 5;
  int actual = s21_strncmp(long_str, short_str, n);

  ck_assert_int_gt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncmp_registr) {
  // Test: s21_strncmp корректно отрабатывает регистрозависимые строки
  const char *upper_str = "S21_string";
  const char *lower_str = "s21_string";
  s21_size_t n = 5;
  int actual = s21_strncmp(upper_str, lower_str, n);

  ck_assert_int_lt(actual, 0);
}
END_TEST

START_TEST(test_s21_strncpy_correct_full) {
  // Test: s21_strncpy корректно отрабатывает полное копирование
  char dest[20] = {0};
  const char *src = "s21_string";
  s21_size_t n = strlen(src) + 1;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_ptr_eq(actual, dest);
  ck_assert_str_eq(dest, src);
  ck_assert_int_eq(dest[n - 1], '\0');
}
END_TEST

START_TEST(test_s21_strncpy_correct_part) {
  // Test: s21_strncpy корректно отрабатывает частичное копирование
  char src[] = "s21_string";
  char dest[20] = {0};
  char expected[20] = {0};
  s21_size_t n = 5;
  strncpy(expected, src, n);
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_str_eq(dest, expected);
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_n_eq_zero) {
  // Test: s21_strncpy корректно отрабатывает случай, если n = 0
  char src[] = "s21_string";
  char dest[20] = "new_string";
  char expected[20] = "new_string";
  s21_size_t n = 0;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_str_eq(dest, expected);
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_empty_str) {
  // Test: s21_strncpy корректно отрабатывает если src пустой
  char src[] = "";
  char dest[11] = "s21_string";
  char expected[11] = {0};
  s21_size_t n = 5;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_str_eq(dest, expected);
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_null_term) {
  // Test: s21_strncpy корректно отрабатывает копирование нуль-терминатора
  char src[] = "s21_\0string";
  char dest[15] = {0};
  s21_size_t n = 10;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_str_eq(dest, "s21_");
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_invis) {
  // Test: s21_strncpy корректно отрабатывает копирование непечатных символов
  char src[] = "s21_\nst\tring";
  char dest[20] = {0};
  s21_size_t n = 10;
  s21_strncpy(dest, src, n);

  ck_assert_mem_eq(dest, src, n);
  ck_assert_int_eq(dest[4], '\n');
  ck_assert_int_eq(dest[10], '\0');
}
END_TEST

START_TEST(test_s21_strncpy_dest_empty) {
  // Test: s21_strncpy корректно отрабатывает если dest пустой
  char src[] = "s21_string";
  char dest[20] = {0};
  s21_size_t n = 5;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_mem_eq(dest, src, n);
  ck_assert_ptr_eq(actual, dest);
}

START_TEST(test_s21_strncpy_src_less_than_n) {
  // Test: s21_strncpy корректно отрабатывает если длина src меньше n
  char src[] = "s21";
  char dest[10] = "school21";
  s21_size_t n = 6;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_str_eq(dest, "s21");
  ck_assert_int_eq(dest[4], '\0');
  ck_assert_int_eq(dest[5], '\0');
  ck_assert_int_eq(dest[6], '2');
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_src_greater_than_n) {
  // Test: s21_strncpy корректно отрабатывает если длина src больше n
  char src[] = "s21_string";
  char dest[20] = {0};
  s21_size_t n = 5;
  char *actual = s21_strncpy(dest, src, n);

  ck_assert_mem_eq(dest, src, n);
  ck_assert_ptr_eq(actual, dest);
}
END_TEST

START_TEST(test_s21_strncpy_src_null) {
  // Test: s21_strncpy корректно отрабатывает если src = null
  char dest[11] = "s21_string";
  s21_size_t n = 5;
  char *actual = s21_strncpy(dest, NULL, n);

  ck_assert_ptr_eq(actual, NULL);
}
END_TEST

START_TEST(test_s21_strncpy_dest_null) {
  // Test: s21_strncpy корректно отрабатывает если dest = null
  char src[] = "test";
  s21_size_t n = 2;
  char *actual = s21_strncpy(NULL, src, n);

  ck_assert_ptr_eq(actual, NULL);
}
END_TEST

START_TEST(test_s21_strcspn_nonmatch) {
  // Test: s21_strcspn корректно отрабатывает случай, где ни один символ не
  // встречается
  char str[] = "s21_string";
  char str2[] = "vbm87";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strcspn(str, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_match) {
  // Test: s21_strcspn корректно отрабатывает случай, где первый символ
  // содержится в str2
  char str[] = "s21_string";
  char str2[] = "str";
  s21_size_t expected = 0;
  s21_size_t actual = s21_strcspn(str, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_match_middle) {
  // Test: s21_strcspn корректно отрабатывает случай, где символ из str2
  // находится в середине str1
  char str[] = "s21_string";
  char str2[] = "tr";
  s21_size_t expected = 5;
  s21_size_t actual = s21_strcspn(str, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_first_string_empty) {
  // Test: s21_strcspn корректно отрабатывает случай, где str1 пустая
  char str1[] = "";
  char str2[] = "s21_string";
  s21_size_t expected = 0;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_second_string_empty) {
  // Test: s21_strcspn корректно отрабатывает случай, где str2 пустая
  char str1[] = "s21_string";
  char str2[] = "";
  s21_size_t expected = strlen(str1);
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_both_strings_empty) {
  // Test: s21_strcspn корректно отрабатывает случай, где обе строки пустые
  char str1[] = "";
  char str2[] = "";
  s21_size_t expected = 0;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_null_term_search) {
  // Test: s21_strcspn корректно отрабатывает поиск нуль-терминатора
  char str1[] = "s21_\0string";
  char str2[] = "\0";
  s21_size_t expected = 4;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_invis) {
  // Test: s21_strcspn корректно отрабатывает поиск непечатных символов
  char str1[] = "s21_\t\nstring";
  char str2[] = "\n\t";
  s21_size_t expected = 4;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_end_of_first_string) {
  // Test: s21_strcspn корректно отрабатывает случай, когда символ находится в
  // конце str1
  char str1[] = "s21_string";
  char str2[] = "g";
  s21_size_t expected = 9;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_multiple_match) {
  // Test: s21_strcspn корректно отрабатывает случай, когда совпадений несколько
  char str1[] = "s21_string";
  char str2[] = "tri";
  s21_size_t expected = 5;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_registr) {
  // Test: s21_strcspn корректно отрабатывает регистрозависимость
  char str1[] = "s21_String";
  char str2[] = "S";
  s21_size_t expected = 4;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_second_string_doubles) {
  // Test: s21_strcspn корректно отрабатывает дубликаты str2
  char str1[] = "s21_string";
  char str2[] = "mmbbiiff";
  s21_size_t expected = 7;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strcspn_wrong_order) {
  // Test: s21_strcspn корректно отрабатывает случай, когда символы str2 идут не
  // лексикографически
  char str1[] = "s21_string";
  char str2[] = "mbif";
  s21_size_t expected = 7;
  s21_size_t actual = s21_strcspn(str1, str2);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_correct) {
  // Test: s21_strerror корректно отрабатывает обычное значение
  int errnums = 0;
  char *error_message = s21_strerror(errnums);

  ck_assert_str_eq(error_message, "Success");
}
END_TEST

START_TEST(test_s21_strerror_less_then_zero) {
  // Test: s21_strerror корректно отрабатывает значение ошибки меньше ноля
  int errnums = -1;
  char *error_message = s21_strerror(errnums);

  ck_assert_str_eq(error_message, "Unknown error");
}
END_TEST

START_TEST(test_s21_strerror_begger_then_size) {
  // Test: s21_strerror корректно отрабатывает значение ошибки больше размера
  // списка
  int errnums = 1000;
  char *error_message = s21_strerror(errnums);

  ck_assert_str_eq(error_message, "Unknown error");
}
END_TEST

START_TEST(test_s21_strerror_border) {
  // Test: s21_strerror корректно отрабатывает значение на границе списка
  int errnums = 132;
  char *error_message = s21_strerror(errnums);

  ck_assert_str_eq(error_message, "Memory page has hardware error");
}
END_TEST

START_TEST(test_s21_strlen_correct_line) {
  // Test: s21_strlen корректно отрабатывает c валидной строкой
  char *str = "s21_string";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strlen(str);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strlen_empty_string) {
  // Test: s21_strlen корректно отрабатывает с пустой строкой
  char *str = "";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strlen(str);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strlen_space) {
  // Test: s21_strlen корректно отрабатывает с пробелом
  char *str = "s21_ string";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strlen(str);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strlen_invis) {
  // Test: s21_strlen корректно отрабатывает с непечатными символами
  char *str = "s21_\tstring";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strlen(str);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strlen_null_term) {
  // Test: s21_strlen корректно отрабатывает с нуль-терминатором в середине
  // строки
  char *str = "s21_\0string";
  s21_size_t expected = strlen(str);
  s21_size_t actual = s21_strlen(str);

  ck_assert_uint_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_first_symbol) {
  // Test: s21_strpbrk корректно отрабатывает совпадение в первом символе
  char str[] = "s21_string";
  char keys[] = "sxz";
  char *expected = str;
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 's');
}
END_TEST

START_TEST(test_s21_strpbrk_middle) {
  // Test: s21_strpbrk корректно отрабатывает совпадение в середине строки
  char str[] = "s21_string";
  char keys[] = "xyrwo";
  char *expected = strchr(str, 'r');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'r');
}
END_TEST

START_TEST(test_s21_strpbrk_last_symbol) {
  // Test: s21_strpbrk корректно отрабатывает совпадение в последнем символе
  char str[] = "s21_string";
  char keys[] = "xygwo";
  char *expected = strchr(str, 'g');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'g');
}
END_TEST

START_TEST(test_s21_strpbrk_multiple_symbols) {
  // Test: s21_strpbrk корректно отрабатывает совпадение с несколькими символами
  char str[] = "s21_string";
  char keys[] = "strxywo";
  char *expected = strchr(str, 's');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_not_match) {
  // Test: s21_strpbrk корректно отрабатывает отсутствие совпадений
  char str[] = "s21_string";
  char keys[] = "xywo";
  char *expected = NULL;
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strpbrk_first_empty_string) {
  // Test: s21_strpbrk корректно отрабатывает если первая строка пустая
  char str[] = "";
  char keys[] = "s21_string";
  char *expected = NULL;
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strpbrk_second_empty_string) {
  // Test: s21_strpbrk корректно отрабатывает если вторая строка пустая
  char str1[] = "s21_string";
  char str2[] = "";
  char *expected = NULL;
  char *actual = s21_strpbrk(str1, str2);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strpbrk_both_empty_string) {
  // Test: s21_strpbrk корректно отрабатывает если обе строки пустые
  char str[] = "";
  char keys[] = "";
  char *expected = NULL;
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strpbrk_special_symbols) {
  // Test: s21_strpbrk корректно отрабатывает поиск спецсимволов
  char str[] = "s21_\tstring";
  char keys[] = "\t";
  char *expected = strchr(str, '\t');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, '\t');
}
END_TEST

START_TEST(test_s21_strpbrk_numbers) {
  // Test: s21_strpbrk корректно отрабатывает поиск чисел
  char str[] = "s21_string";
  char keys[] = "1";
  char *expected = strchr(str, '1');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, '1');
}
END_TEST

START_TEST(test_s21_strpbrk_registr) {
  // Test: s21_strpbrk корректно отрабатывает регистрозависимость
  char str[] = "s21_String";
  char keys[] = "S";
  char *expected = strchr(str, 'S');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'S');
}
END_TEST

START_TEST(test_s21_strpbrk_first_multiple) {
  // Test: s21_strpbrk корректно отрабатывает дублирующиеся символы в первой
  // строке
  char str[] = "s21_string";
  char keys[] = "s";
  char *expected = strchr(str, 's');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 's');
}
END_TEST

START_TEST(test_s21_strpbrk_second_multiple) {
  // Test: s21_strpbrk корректно отрабатывает дублирующиеся символы во второй
  // строке
  char str[] = "s21_string";
  char keys[] = "tt";
  char *expected = strchr(str, 't');
  char *actual = s21_strpbrk(str, keys);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 't');
}
END_TEST

START_TEST(test_s21_strpbrk_unreach) {
  // Test: s21_strpbrk корректно отрабатывает значения после нуль-терминатора
  char str1[] = "s21_\0string";
  char str2[] = "r";
  char *actual = s21_strpbrk(str1, str2);

  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strpbrk_second_whole_alph) {
  // Test: s21_strpbrk корректно отрабатывает совпадение с алфавитом
  char str1[] = "s21_string";
  char str2[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *expected = str1;
  char *actual = s21_strpbrk(str1, str2);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 's');
}
END_TEST

START_TEST(test_s21_strpbrk_second_space) {
  // Test: s21_strpbrk корректно отрабатывает совпадение с пробелом
  char str1[] = "s21_ string";
  char str2[] = " ";
  char *expected = strpbrk(str1, str2);
  char *actual = s21_strpbrk(str1, str2);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, ' ');
}
END_TEST

START_TEST(test_s21_strrchr_single_match) {
  // Test: s21_strrchr корректно отрабатывает единственное совпадение
  char str[] = "s21_string";
  int c = 't';
  char *expected = str + 5;
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 't');
}
END_TEST

START_TEST(test_s21_strrchr_multiple_match) {
  // Test: s21_strrchr корректно отрабатывает множественное совпадение
  char str[] = "s21_string";
  int c = 's';
  char *expected = str + 4;
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 's');
}
END_TEST

START_TEST(test_s21_strrchr_last_symbol) {
  // Test: s21_strrchr корректно отрабатывает совпадение в конце строки
  char str[] = "s21_string";
  int c = 'g';
  char *expected = str + 9;
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'g');
}
END_TEST

START_TEST(test_s21_strrchr_first_symbol) {
  // Test: s21_strrchr корректно отрабатывает совпадение в начале строки
  char str[] = "a_s21_string";
  int c = 'a';
  char *expected = str;
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'a');
}
END_TEST

START_TEST(test_s21_strrchr_not_match) {
  // Test: s21_strrchr корректно отрабатывает отсутствие совпадений
  char str[] = "s21_string";
  int c = 'a';
  char *expected = strrchr(str, c);
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(expected, actual);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
  // Test: s21_strrchr корректно отрабатывает пустую строку
  char str[] = "";
  int c = 'a';
  char *expected = strrchr(str, c);
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(expected, actual);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strrchr_null_term_search) {
  // Test: s21_strrchr корректно отрабатывает поиск нуль-терминатора
  char str[] = "s21_\0str\0ing";
  char *expected = strrchr(str, '\0');
  char *actual = s21_strrchr(str, '\0');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, '\0');
}
END_TEST

START_TEST(test_s21_strrchr_special_symbol) {
  // Test: s21_strrchr корректно отрабатывает поиск спецсимвола
  char str[] = "s21_str\ting";
  char *expected = strrchr(str, '\t');
  char *actual = s21_strrchr(str, '\t');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, '\t');
}
END_TEST

START_TEST(test_s21_strrchr_registr) {
  // Test: s21_strrchr корректно отрабатывает регистрозависимость
  char str[] = "S21_str\ting";
  char *expected = strrchr(str, 'S');
  char *actual = s21_strrchr(str, 'S');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_int_eq(*actual, 'S');
}
END_TEST

START_TEST(test_s21_strrchr_null_term) {
  //- Test: s21_strrchr корректно отрабатывает поиск после нуль-терминатора
  char str[] = "s21_str\0ing";
  char *expected = strrchr(str, 'i');
  char *actual = s21_strrchr(str, 'i');

  ck_assert_ptr_eq(actual, expected);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strrchr_numbers) {
  // Test: s21_strrchr корректно отрабатывает цифры в строке
  char str[] = "s21_string";
  int c = '2';
  char *expected = strrchr(str, c);
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(expected, actual);
  ck_assert_int_eq(*actual, '2');
}
END_TEST

START_TEST(test_s21_strrchr_space) {
  //- Test: s21_strrchr корректно отрабатывает пробел в строке
  char str[] = "s21_ string";
  int c = ' ';
  char *expected = strrchr(str, c);
  char *actual = s21_strrchr(str, c);

  ck_assert_ptr_eq(expected, actual);
  ck_assert_int_eq(*actual, ' ');
}
END_TEST

START_TEST(test_s21_strstr_match_at_start) {
  // Test: s21_strstr корректно отрабатывает подстроку в начале
  char str[] = "s21_string";
  char substr[] = "s21";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_match_in_the_middle) {
  // Test: s21_strstr корректно отрабатывает подстроку в середине
  char str[] = "s21_string";
  char substr[] = "str";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_match_in_the_end) {
  // Test: s21_strstr корректно отрабатывает подстроку в конце
  char str[] = "s21_string";
  char substr[] = "ing";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_full_match) {
  //- Test: s21_strstr корректно отрабатывает совпадение строки и подстроки
  char str[] = "s21_string";
  char substr[] = "s21_string";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_not_match) {
  // Test: s21_strstr корректно отрабатывает отсутствие совпадений
  char str[] = "s21_string";
  char substr[] = "miss";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_first_string_empty) {
  // Test: s21_strstr корректно отрабатывает если первая строка пустая
  char str[] = "";
  char substr[] = "miss";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_second_string_empty) {
  // Test: s21_strstr корректно отрабатывает если вторая строка пустая
  char str[] = "s21_string";
  char substr[] = "";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_both_strings_empty) {
  // Test: s21_strstr корректно отрабатывает если обе строки пустые
  char str[] = "";
  char substr[] = "";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_special_symbols) {
  // Test: s21_strstr корректно отрабатывает спецсимволы
  char str[] = "s21_$tring";
  char substr[] = "$";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_numbers) {
  // Test: s21_strstr корректно отрабатывает цифры
  char str[] = "s21_$tring";
  char substr[] = "21";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_register) {
  // Test: s21_strstr корректно отрабатывает регистрозависимость
  char str[] = "s21_String";
  char substr[] = "Str";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_repeatable_symbols) {
  // Test: s21_strstr корректно отрабатывает повторяющиеся символы
  char str[] = "s21_string";
  char substr[] = "s";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_overlay) {
  // Test: s21_strstr корректно отрабатывает перекрывающиеся подстроки
  char str[] = "s21_stririring";
  char substr[] = "iri";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_partial) {
  // Test: s21_strstr корректно отрабатывает частичные совпадения
  char str[] = "s21_string";
  char substr[] = "stre";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_long_string) {
  // Test: s21_strstr корректно отрабатывает если длина подстроки больше строки
  char str[] = "s21_str";
  char substr[] = "s21_string";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_null_term) {
  // Test: s21_strstr корректно отрабатывает строки с нуль-терминатором в
  // середине
  char str[20] = "s21_\0string";
  char substr[] = "string";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_one_symbol) {
  // Test: s21_strstr корректно отрабатывает подстроку в один символ
  char str[] = "s21_string";
  char substr[] = "t";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strstr_space) {
  // Test: s21_strstr корректно отрабатывает пробел
  char str[] = "s21_ string";
  char substr[] = " ";
  char *actual = s21_strstr(str, substr);
  char *expected = strstr(str, substr);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strtok_simple) {
  // Test: s21_strtok корректно отрабатывает простую токенизацию
  char str[] = "s21, string, test";
  char *delim = ",";
  char *expected_tokens[] = {"s21", " string", " test"};
  char *actual;
  int i = 0;
  actual = s21_strtok(str, delim);
  ck_assert_str_eq(actual, expected_tokens[i++]);
  while ((actual = s21_strtok(NULL, delim))) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
  }

  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_strtok_diff_delim) {
  // Test: s21_strtok корректно отрабатывает разные разделители
  char str[] = "s21|string;test,case";
  char *delims = "|;,";
  char *expected_tokens[] = {"s21", "string", "test", "case"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }

  ck_assert_int_eq(i, 4);
}
END_TEST

START_TEST(test_s21_strtok_empty_str) {
  // Test: s21_strtok корректно отрабатывает пустую строку
  char str[] = "";
  char *delims = " ,;";
  char *expected = NULL;
  char *actual = s21_strtok(str, delims);

  ck_assert_ptr_eq(actual, expected);
  actual = s21_strtok(NULL, delims);
  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strtok_str_of_delim) {
  // Test: s21_strtok корректно отрабатывает только разделители
  char str[] = "|;,";
  char *delims = "|;,";
  char *actual;

  actual = s21_strtok(str, delims);
  ck_assert_ptr_null(actual);
}
END_TEST

START_TEST(test_s21_strtok_delim_first) {
  // Test: s21_strtok корректно отрабатывает разделитель в начале
  char str[] = "|s21|string|test";
  char *delims = "|";
  char *expected_tokens[] = {"s21", "string", "test"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }
  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_strtok_delim_last) {
  // Test: s21_strtok корректно отрабатывает разделитель в конце
  char str[] = "s21|string|test|";
  char *delims = "|";
  char *expected_tokens[] = {"s21", "string", "test"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }
  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_strtok_delim_first_and_last) {
  // Test: s21_strtok корректно отрабатывает разделители с двух сторон
  char str[] = "|s21|string|test|";
  char *delims = "|";
  char *expected_tokens[] = {"s21", "string", "test"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }
  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_strtok_registr) {
  // Test: s21_strtok корректно отрабатывает регистрозависимость
  char str[] = "s21_String_test";
  char *delims = "s";
  char *expected_tokens[] = {"21_String_te", "t"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }
  ck_assert_int_eq(i, 2);
}
END_TEST

START_TEST(test_s21_strtok_tabs) {
  // Test: s21_strtok корректно отрабатывает управляющие символы как разделители
  char str[] = "s21\tstring\t\ttest\t";
  char *delims = "\t";
  char *expected_tokens[] = {"s21", "string", "test"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, delims);
  while (actual != NULL) {
    ck_assert_str_eq(actual, expected_tokens[i++]);
    actual = s21_strtok(NULL, delims);
  }
  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_strtok_change_of_delim) {
  // Test: s21_strtok корректно отрабатывает изменение разделителей между
  // вызовами
  char str[] = "s21_,string test;strtok";
  char *expected_tokens[] = {"s21_", "string", "test", "strtok"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, ",");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, " ");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, ";");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, ";");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  ck_assert_int_eq(i, 4);
}
END_TEST

START_TEST(test_s21_strtok_delim_expand) {
  // Test: s21_strtok корректно отрабатывает расширение набора разделителей
  char str[] = "s21_,string test;strtok";
  char *expected_tokens[] = {"s21_", "string", "test", "strtok"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, ",");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, ", ");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, ", ;");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, ", ;");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  ck_assert_int_eq(i, 4);
}
END_TEST

START_TEST(test_s21_strtok_delim_num) {
  // Test: s21_strtok корректно отрабатывает разделитель цифру
  char str[] = "s21_1string1test";
  char *expected_tokens[] = {"s2", "_", "string", "test"};
  char *actual;
  int i = 0;

  actual = s21_strtok(str, "1");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, "1");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  actual = s21_strtok(NULL, "1");
  ck_assert_str_eq(actual, expected_tokens[i++]);

  ck_assert_int_eq(i, 3);
}
END_TEST

START_TEST(test_s21_sprintf_char) {
  // Test: c стандартный символ
  char buffer_act[2] = {0};
  char buffer_exp[2] = {0};
  int actual = s21_sprintf(buffer_act, "%c", 'A');
  int expected = sprintf(buffer_exp, "%c", 'A');

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_l_char) {
  // Test: c стандартный символ
  char buffer_act[8] = {0};
  char buffer_exp[8] = {0};
  int actual = s21_sprintf(buffer_act, "%lc", 'A');
  int expected = sprintf(buffer_exp, "%lc", 'A');

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_special) {
  // Test: c спецсимвол
  char buffer_act[8] = {0};
  char buffer_exp[8] = {0};
  int actual;
  int expected;
  actual = s21_sprintf(buffer_act, "%c", '$');
  expected = sprintf(buffer_exp, "%c", '$');

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_invis) {
  //- Test: c непечатный символ
  char buffer_act[2] = {0};
  char buffer_exp[2] = {0};
  int actual;
  int expected;
  actual = s21_sprintf(buffer_act, "%c", '\t');
  expected = sprintf(buffer_exp, "%c", '\t');

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_positive) {
  // Test: d положительный
  char buffer_act[3] = {0};
  char buffer_exp[3] = {0};
  int number = 21;
  int actual = s21_sprintf(buffer_act, "%d", number);
  int expected = sprintf(buffer_exp, "%d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_negative) {
  // Test: d отрицательный
  char buffer_act[4] = {0};
  char buffer_exp[4] = {0};
  int number = -21;
  int actual = s21_sprintf(buffer_act, "%d", number);
  int expected = sprintf(buffer_exp, "%d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_zero) {
  // Test: d ноль
  char buffer_act[3] = {0};
  char buffer_exp[3] = {0};
  int number = 0;
  int actual = s21_sprintf(buffer_act, "%d", number);
  int expected = sprintf(buffer_exp, "%d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_intmax) {
  // Test: d инт_макс
  char buffer_act[12] = {0};
  char buffer_exp[12] = {0};

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(sprintf(buffer_act, "%d", INT_MAX),
                   s21_sprintf(buffer_exp, "%d", INT_MAX));
}
END_TEST

START_TEST(test_s21_sprintf_d_intmin) {
  // Test: d инт_мин
  char buffer_act[13] = {0};
  char buffer_exp[13] = {0};

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(sprintf(buffer_act, "%d", INT_MAX),
                   s21_sprintf(buffer_exp, "%d", INT_MAX));
}
END_TEST

START_TEST(test_s21_sprintf_space) {
  // Test: d и пробел (% d)
  char buffer_act[4] = {0};
  char buffer_exp[4] = {0};
  int number = 21;
  int actual = s21_sprintf(buffer_act, "% d", number);
  int expected = sprintf(buffer_exp, "% d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_plus) {
  // Test: d и плюс (%+d)
  char buffer_act[4] = {0};
  char buffer_exp[4] = {0};
  int number = -21;
  int actual = s21_sprintf(buffer_act, "%+d", number);
  int expected = sprintf(buffer_exp, "%+d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_width) {
  // Test: d + width - форматирование по ширине (%3d)
  char buffer_exp[4] = {0};
  char buffer_act[4] = {0};
  int number = 21;
  int expected;
  int actual;
  actual = s21_sprintf(buffer_act, "%3d", number);
  expected = sprintf(buffer_exp, "%3d", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d_width_minus) {
  // Test: d + width + флаг - - форматирование по ширине (%-3d)
  char buffer_act[4] = {0};
  char buffer_exp[4] = {0};
  int expected = sprintf(buffer_exp, "%-3d", 21);
  int actual = s21_sprintf(buffer_act, "%-3d", 21);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_usual) {
  // Test: f обычное значение
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.456;
  int expected = sprintf(buffer_exp, "%f", number);
  int actual = s21_sprintf(buffer_act, "%f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_plus) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.456;
  int expected = sprintf(buffer_exp, "%+f", number);
  int actual = s21_sprintf(buffer_act, "%+f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_plus_negative) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.456;
  int expected = sprintf(buffer_exp, "%+f", number);
  int actual = s21_sprintf(buffer_act, "%+f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_plus_zero_zero) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 0.0;
  int expected = sprintf(buffer_exp, "%+f", number);
  int actual = s21_sprintf(buffer_act, "%+f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_space) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.456;
  int expected = sprintf(buffer_exp, "% f", number);
  int actual = s21_sprintf(buffer_act, "% f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_space_negative) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = -123.456;
  int expected = sprintf(buffer_exp, "% f", number);
  int actual = s21_sprintf(buffer_act, "% f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_space_zero_zero) {
  // Test: f+
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 0.0;
  int expected = sprintf(buffer_exp, "% f", number);
  int actual = s21_sprintf(buffer_act, "% f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_zero_zero) {
  // Test: f 0.0
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 0.0;
  int expected = sprintf(buffer_exp, "%f", number);
  int actual = s21_sprintf(buffer_act, "%f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_minus_zero_zero) {
  // Test: f -0.0
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = -0.0;
  int expected = sprintf(buffer_exp, "%f", number);
  int actual = s21_sprintf(buffer_act, "%f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision) {
  // Test: f + precision - форматирование по точности (%.2f)
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.9999;
  int expected = sprintf(buffer_exp, "%.2f", number);
  int actual = s21_sprintf(buffer_act, "%.2f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_and_width) {
  // Test: f + precision - форматирование по точности и ширине (%10.3f)
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  double number = 123.4567;
  int expected = sprintf(buffer_exp, "%10.3f", number);
  int actual = s21_sprintf(buffer_act, "%10.3f", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_usual) {
  // Test: s базовый случай
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  const char *str = "s21_string";
  int expected = sprintf(buffer_exp, "%s", str);
  int actual = s21_sprintf(buffer_act, "%s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_long) {
  // Test: s базовый случай
  char buffer_act[128] = {0};
  char buffer_exp[128] = {0};
  wchar_t *str = L"s21_string";
  int expected = sprintf(buffer_exp, "%ls", str);
  int actual = s21_sprintf(buffer_act, "%ls", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_long_null) {
  // Test: s базовый случай
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  wchar_t *str = NULL;
  int expected = sprintf(buffer_exp, "%ls", str);
  int actual = s21_sprintf(buffer_act, "%ls", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_empty_string) {
  // Test: s пустая строка
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  const char *str = "";
  int expected = sprintf(buffer_exp, "%s", str);
  int actual = s21_sprintf(buffer_act, "%s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_width) {
  // - Test: s + width                (%10s)
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  const char *str = "s21";
  int expected = sprintf(buffer_exp, "%10s", str);
  int actual = s21_sprintf(buffer_act, "%10s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_minus) {
  // - Test: s + width                (%10s)
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  const char *str = "s21";
  int expected = sprintf(buffer_exp, "%-10s", str);
  int actual = s21_sprintf(buffer_act, "%-10s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_low_minus) {
  // - Test: s + width                (%10s)
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};
  const char *str = "s21_string";
  int expected = sprintf(buffer_exp, "%-10s", str);
  int actual = s21_sprintf(buffer_act, "%-10s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
  // Test: s + precision            (%.3s)
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  const char *str = "s21_string";
  int expected = sprintf(buffer_exp, "%.3s", str);
  int actual = s21_sprintf(buffer_act, "%.3s", str);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_usual) {
  // Test: u Стандартное значение
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  unsigned int value = 12345;
  int expected = sprintf(buffer_exp, "%u", value);
  int actual = s21_sprintf(buffer_act, "%u", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_h_usual) {
  // Test: u Стандартное значение
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  unsigned int value = 12345;
  int expected = sprintf(buffer_exp, "%hu", value);
  int actual = s21_sprintf(buffer_act, "%hu", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_l_usual) {
  // Test: u Стандартное значение
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  long unsigned int value = 12345;
  int expected = sprintf(buffer_exp, "%lu", value);
  int actual = s21_sprintf(buffer_act, "%lu", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero) {
  //- Test: u 0
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  unsigned int value = 0;
  int expected = sprintf(buffer_exp, "%u", value);
  int actual = s21_sprintf(buffer_act, "%u", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero_precision) {
  //- Test: u .0
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  unsigned int value = 0;
  int expected = sprintf(buffer_exp, "%.0u", value);
  int actual = s21_sprintf(buffer_act, "%.0u", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  // Test: % одиночный
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int expected = sprintf(buffer_exp, "%%");
  int actual = s21_sprintf(buffer_act, "%%");

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_percent_combined) {
  // Test: % в комбинации (100%%)
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int expected = sprintf(buffer_exp, "100%%");
  int actual = s21_sprintf(buffer_act, "100%%");

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_i_positive) {
  // Test: i положительный
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = 12345;
  int expected = sprintf(buffer_exp, "%i", value);
  int actual = s21_sprintf(buffer_act, "%i", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_i_negative) {
  // Test: i отрицательный
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = -12345;
  int expected = sprintf(buffer_exp, "%i", value);
  int actual = s21_sprintf(buffer_act, "%i", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_i_zero) {
  // Test: i ноль
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = 0;
  int expected = sprintf(buffer_exp, "%i", value);
  int actual = s21_sprintf(buffer_act, "%i", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_i_int_max) {
  // Test: i инт_макс
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(sprintf(buffer_exp, "%i", INT_MAX),
                   s21_sprintf(buffer_act, "%i", INT_MAX));
}
END_TEST

START_TEST(test_s21_sprintf_i_int_min) {
  // Test: i инт_мин
  char buffer_act[15] = {0};
  char buffer_exp[15] = {0};

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(sprintf(buffer_exp, "%i", INT_MIN),
                   s21_sprintf(buffer_act, "%i", INT_MIN));
}
END_TEST

START_TEST(test_s21_sprintf_i_width) {
  // Test: i + width - форматирование по ширине (%3d)
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int number = 21;
  int expected = sprintf(buffer_exp, "%3i", number);
  int actual = s21_sprintf(buffer_act, "%3i", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_i_width_minus) {
  // Test: i + width - форматирование по ширине (%-3d)
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int number = 21;
  int expected = sprintf(buffer_exp, "%-3d", number);
  int actual = s21_sprintf(buffer_act, "%-3d", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_act, buffer_exp);
}
END_TEST

START_TEST(test_s21_sprintf_width_char) {
  // Test: ширина для %с
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  char ch = 's';
  int expected = sprintf(buffer_exp, "%5c", ch);
  int actual = s21_sprintf(buffer_act, "%5c", ch);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_precision_zero_for_d) {
  // Test: точность 0 для %d
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = 0;
  int expected = sprintf(buffer_act, "%.0d", value);
  int actual = s21_sprintf(buffer_exp, "%.0d", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_precision_border_for_d) {
  // Test: точность 0 для %d
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = 0;
  int expected = sprintf(buffer_act, "%.9d", value);
  int actual = s21_sprintf(buffer_exp, "%.9d", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_width_zero_for_d) {
  // Test: точность 0 для %d
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  int value = 0;
  int expected = sprintf(buffer_act, "%0d", value);
  int actual = s21_sprintf(buffer_exp, "%0d", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u_precision) {
  // Test: точность для %u
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  unsigned int value = 21;
  int expected = sprintf(buffer_exp, "%.5u", value);
  int actual = s21_sprintf(buffer_act, "%.5u", value);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_act, buffer_exp);
}
END_TEST

START_TEST(test_s21_sprintf_short_int) {
  // Test: %hd для short int
  char buffer_act[10] = {0};
  char buffer_exp[10] = {0};
  short int value = -12345;
  int expected = sprintf(buffer_exp, "%hd", value);
  int actual = s21_sprintf(buffer_act, "%hd", value);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_long_int) {
  // Test: %ld для long int
  char buffer_act[20] = {0};
  char buffer_exp[20] = {0};
  long int value = 1234567890L;
  int expected = sprintf(buffer_exp, "%ld", value);
  int actual = s21_sprintf(buffer_act, "%ld", value);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_act, buffer_exp);
}
END_TEST

START_TEST(test_s21_sprintf_long_float) {
  // Test: %lf для long float
  char buffer_act[20] = {0};
  char buffer_exp[20] = {0};
  double value = 1.23456;
  int expected = sprintf(buffer_exp, "%lf", value);
  int actual = s21_sprintf(buffer_act, "%lf", value);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_act, buffer_exp);
}
END_TEST

START_TEST(test_s21_sprintf_x_upper) {
  // Test: %X - бонус
  char buffer_exp[20] = {0};
  char buffer_act[20] = {0};
  unsigned int value = 255;
  int expected = sprintf(buffer_exp, "%X", value);
  int actual = s21_sprintf(buffer_act, "%X", value);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_exp, buffer_act);
}
END_TEST

START_TEST(test_s21_sprintf_x_low) {
  // Test: %x - бонус
  char buffer_exp[20] = {0};
  char buffer_act[20] = {0};
  unsigned int value = 255;
  int expected = sprintf(buffer_exp, "%x", value);
  int actual = s21_sprintf(buffer_act, "%x", value);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_exp, buffer_act);
}
END_TEST

START_TEST(test_s21_sprintf_g) {
  //- Test: %g - бонус
  char buffer_act[32] = {0};
  char buffer_exp[32] = {0};
  double number = 0.000012345;
  int expected = sprintf(buffer_exp, "%g", number);
  int actual = s21_sprintf(buffer_act, "%g", number);

  ck_assert_str_eq(buffer_exp, buffer_act);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_g_short) {
  //- Test: %g - бонус
  char buffer_act[32] = {0};
  char buffer_exp[32] = {0};
  double number = 123.45;
  int expected = sprintf(buffer_exp, "%3g", number);
  int actual = s21_sprintf(buffer_act, "%3g", number);

  ck_assert_str_eq(buffer_exp, buffer_act);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_g_short_zero) {
  //- Test: %g - бонус
  char buffer_act[32] = {0};
  char buffer_exp[32] = {0};
  double number = 1230.0;
  int expected = sprintf(buffer_exp, "%3g", number);
  int actual = s21_sprintf(buffer_act, "%3g", number);

  ck_assert_str_eq(buffer_exp, buffer_act);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_all_mods) {
  // Test: все модификаторы %-+4.5ld"
  char buffer_act[64] = {0};
  char buffer_exp[64] = {0};
  long int number = 12345L;
  int actual = s21_sprintf(buffer_act, "%-+4.5ld", number);
  int expected = sprintf(buffer_exp, "%-+4.5ld", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_all_specs) {
  // Test: разные спецификаторы в строке %c %d %f %s
  char buffer_act[128] = {0};
  char buffer_exp[128] = {0};
  char char_val = 's';
  int int_val = 2;
  double double_val = 1.0;
  const char *str_val = "_string";
  int actual = s21_sprintf(buffer_act, "%c%d%.0f%s", char_val, int_val,
                           double_val, str_val);
  int expected =
      sprintf(buffer_exp, "%c%d%.0f%s", char_val, int_val, double_val, str_val);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_incorrect) {
  // - Test: incorrect specifier
  char buffer_act[15] = {0};
  s21_sprintf(buffer_act, "%z");

  ck_assert_str_eq(buffer_act, "%z");
}
END_TEST

START_TEST(test_s21_sprintf_float) {
  // Test: # для float - бонус
  char buffer[64] = {0};
  char buffer_std[64] = {0};
  double number = 21.0;
  int actual = s21_sprintf(buffer, "%#f", number);
  int expected = sprintf(buffer_std, "%#f", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision_bonus) {
  // Test: s + precision            (%*s)(бонус)
  char buffer[15] = {0};
  char buffer_std[15] = {0};
  const char *str = "s21_string";
  int precision = 4;
  s21_sprintf(buffer, "%.*s", precision, str);
  sprintf(buffer_std, "%.*s", precision, str);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_d_width_bonus) {
  // Test: d + width - форматирование по ширине (%*d) (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  int number = 21;
  int width = 5;
  s21_sprintf(buffer, "%*d", width, number);
  sprintf(buffer_std, "%*d", width, number);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_bonus) {
  // Test: f + precision - форматирование по точности (%.*f)   (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  double number = 1.23456789;
  int precision = 4;
  int actual = s21_sprintf(buffer, "%.*f", precision, number);
  int expected = sprintf(buffer_std, "%.*f", precision, number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_and_width_bonus) {
  // Test: f + precision - форматирование по точности и ширине (%*.*f) (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  double number = 1.23456789;
  int precision = 4;
  int width = 10;
  int actual = s21_sprintf(buffer, "%*.*f", width, precision, number);
  int expected = sprintf(buffer_std, "%*.*f", width, precision, number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_bonus) {
  // Test: s + width                (%*s) (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  const char *str = "s21_string";
  int width = 5;
  int actual = s21_sprintf(buffer, "%*s", width, str);
  int expected = sprintf(buffer_std, "%*s", width, str);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_i_width_bonus) {
  // Test: i + width - форматирование по ширине (%*d) (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  int number = 21;
  int width = 5;
  int actual = s21_sprintf(buffer, "%*d", width, number);
  int expected = sprintf(buffer_std, "%*d", width, number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_negative_width_bonus) {
  // Test: отрицательная ширина со звездой с %d (%*d, -5, 10) (бонус)
  char buffer_act[32] = {0};
  char buffer_exp[32] = {0};
  int number = 21;
  int width = -5;
  int actual = s21_sprintf(buffer_act, "%*d", width, number);
  int expected = sprintf(buffer_exp, "%*d", width, number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_percent_o_bonus) {
  // Test: %o (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  unsigned int number = 255;
  int actual = s21_sprintf(buffer, "%o", number);
  int expected = sprintf(buffer_std, "%o", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_percent_p_bonus) {
  // Test: %p (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  void *ptr = (void *)21;
  int s21_len = s21_sprintf(buffer, "%p", ptr);
  int std_len = sprintf(buffer_std, "%p", ptr);

  ck_assert_int_eq(s21_len, std_len);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_percent_p_null) {
  // Test: %p null
  char buffer_exp[32] = {0};
  char buffer_act[32] = {0};
  void *ptr = (void *)0;
  int expected = s21_sprintf(buffer_exp, "%p", ptr);
  int actual = s21_sprintf(buffer_act, "%p", ptr);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_sharp_x_bonus) {
  // Test: #x (бонус)
  char buffer_act[32] = {0};
  char buffer_exp[32] = {0};
  unsigned int number = 255;
  int actual = s21_sprintf(buffer_act, "%#x", number);
  int expected = sprintf(buffer_exp, "%#x", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer_act, buffer_exp);
}
END_TEST

START_TEST(test_s21_sprintf_sharp_o_bonus) {
  // Test: #o (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  unsigned int number = 255;
  int actual = s21_sprintf(buffer, "%#o", number);
  int expected = sprintf(buffer_std, "%#o", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_sharp_g_bonus) {
  // Test: #g (бонус)
  char buffer[32] = {0};
  char buffer_std[32] = {0};
  double number = 21.0;
  int actual = s21_sprintf(buffer, "%#g", number);
  int expected = sprintf(buffer_std, "%#g", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_bonus) {
  // Test: %Lf (бонус)
  char buffer_act[64] = {0};
  char buffer_exp[64] = {0};
  long double number = 12345.6789L;
  int actual = s21_sprintf(buffer_act, "%Lf", number);
  int expected = sprintf(buffer_exp, "%Lf", number);

  ck_assert_str_eq(buffer_act, buffer_exp);
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_sprintf_Le_bonus) {
  // Test: %Le (бонус)
  char buffer[64] = {0};
  char buffer_std[64] = {0};
  long double number = 12345000000.6789L;
  int actual = s21_sprintf(buffer, "%Le", number);
  int expected = sprintf(buffer_std, "%Le", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_LE_bonus) {
  // Test: %LE (бонус)
  char buffer[64] = {0};
  char buffer_std[64] = {0};
  long double number = 12345.6789L;
  int actual = s21_sprintf(buffer, "%LE", number);
  int expected = sprintf(buffer_std, "%LE", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_Lg_bonus) {
  // Test: %Lg (бонус)
  char buffer[64] = {0};
  char buffer_std[64] = {0};
  long double number = 12345.6789L;
  int actual = s21_sprintf(buffer, "%Lg", number);
  int expected = sprintf(buffer_std, "%Lg", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_bonus_inf) {
  // Test: %Lf на INFINITY (бонус)
  char buffer[1024] = {0};
  long double number = INFINITY;
  s21_sprintf(buffer, "%Lf", number);

  ck_assert_str_eq(buffer, "inf");
}
END_TEST

START_TEST(test_s21_sprintf_Lf_bonus_minus_inf) {
  // Test: %Lf на -INFINITY (бонус)
  char buffer[1024] = {0};
  long double number = -INFINITY;
  s21_sprintf(buffer, "%Lf", number);

  ck_assert_str_eq(buffer, "-inf");
}
END_TEST

START_TEST(test_s21_sprintf_Lf_bonus_nan) {
  // Test: %Lf на NAN (бонус)
  char buffer[64] = {0};
  char buffer_std[64] = {0};
  long double number = NAN;
  int actual = s21_sprintf(buffer, "%Lf", number);
  int expected = sprintf(buffer_std, "%Lf", number);

  ck_assert_int_eq(actual, expected);
  ck_assert_str_eq(buffer, buffer_std);
}
END_TEST

START_TEST(test_s21_to_upper_usual) {
  // Test: Функция отрабатывает корректно на обычной строке
  char input[] = "string|";
  char expected[] = "STRING|";
  char *actual = s21_to_upper(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_upper_uppercased) {
  // Test: Функция отрабатывает корректно на строке с заглавными буквами
  char input[] = "STRING";
  char expected[] = "STRING";
  char *actual = s21_to_upper(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_upper_empty_str) {
  // Test: Функция отрабатывает корректно на пустой строке
  char input[] = "";
  char expected[] = "";
  char *actual = s21_to_upper(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_upper_nums_chars) {
  // Test: Функция отрабатывает корректно на строке с цифрами и символами
  char input[] = "s21_string";
  char expected[] = "S21_STRING";
  char *actual = s21_to_upper(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_upper_null) {
  // Test: Функция отрабатывает корректно при строке = NULL
  char *actual = s21_to_upper(NULL);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_lower_usual) {
  // Test: Функция отрабатывает корректно на обычной строке
  char input[] = "STRING";
  char expected[] = "string";
  char *actual = s21_to_lower(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_lower_lowercased) {
  // Test: Функция отрабатывает корректно на строке со строчными буквами
  char input[] = "string";
  char expected[] = "string";
  char *actual = s21_to_lower(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_lower_empty_str) {
  // Test: Функция отрабатывает корректно на пустой строке
  char input[] = "";
  char expected[] = "";
  char *actual = s21_to_lower(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_lower_nums_chars) {
  //- Test: Функция отрабатывает корректно на строке с цифрами и символами
  char input[] = "S21_STRING";
  char expected[] = "s21_string";
  char *actual = s21_to_lower(input);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_to_lower_null) {
  // Test: Функция отрабатывает корректно при строке = NULL
  char *actual = s21_to_lower(NULL);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_usual) {
  // Test: Функция отрабатывает корректно с обычной вставкой
  const char src[] = "string";
  const char str[] = "21_s";
  s21_size_t start_index = 1;
  char expected[] = "s21_string";
  char *actual = s21_insert(src, str, start_index);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_empty_into_full) {
  // Test: Функция отрабатывает корректно со вставкой пустой строки в обычную
  // строку
  const char src[] = "s21_string";
  const char str[] = "";
  s21_size_t start_index = 1;
  char expected[] = "s21_string";
  char *actual = s21_insert(src, str, start_index);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_full_into_empty) {
  // Test: Функция отрабатывает корректно со вставкой обычной строки в пустую
  // строку
  const char src[] = "";
  const char str[] = "s21_string";
  s21_size_t start_index = 0;
  char expected[] = "s21_string";
  char *actual = s21_insert(src, str, start_index);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_into_start) {
  // Test: Функция отрабатывает корректно со вставкой обычной строки в начало
  // строки
  const char src[] = "string";
  const char str[] = "s21_";
  s21_size_t start_index = 0;
  char expected[] = "s21_string";
  char *actual = s21_insert(src, str, start_index);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_into_end) {
  // Test: Функция отрабатывает корректно со вставкой обычной строки в конец
  // строки
  const char src[] = "s21_";
  const char str[] = "string";
  s21_size_t start_index = 4;
  char expected[] = "s21_string";
  char *actual = s21_insert(src, str, start_index);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_unreach) {
  // Test: Функция отрабатывает корректно со вставкой обычной строки за границы
  // массива
  const char src[] = "string";
  const char str[] = "s21_";
  s21_size_t start_index = 10;
  char *actual = s21_insert(src, str, start_index);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_into_null) {
  // Test: Функция отрабатывает корректно со вставкой строки в NULL
  const char str[] = "s21_";
  s21_size_t start_index = 0;
  char *actual = s21_insert(NULL, str, start_index);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_insert_mull_into_string) {
  // Test: Функция отрабатывает корректно со вставкой NULL в строку
  const char src[] = "string";
  s21_size_t start_index = 0;
  char *actual = s21_insert(src, NULL, start_index);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_space) {
  // Test: Функция отрабатывает корректно с пробелом
  const char src[] = "   s21_string   ";
  const char trim_chars[] = " ";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_copies) {
  // Test: Функция отрабатывает корректно c несколькими повторяющимися символами
  const char src[] = "****s21_string****";
  const char trim_chars[] = "*";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_diff_symbols) {
  // Test: Функция отрабатывает корректно несколькими разными символами
  const char src[] = "**s21_string##";
  const char trim_chars[] = "*#";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_no_match) {
  // Test: Функция отрабатывает корректно без совпадений
  const char src[] = "s21_string";
  const char trim_chars[] = "*#";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_full_trim) {
  // Test: Функция отрабатывает корректно если строка состоит из символов для
  // обрезки
  const char src[] = "**##";
  const char trim_chars[] = "*#";
  char expected[] = "";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_empty_string) {
  // Test: Функция отрабатывает корректно с пустой строкой
  const char src[] = "";
  const char trim_chars[] = "*#";
  char expected[] = "";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_empty_trim) {
  // Test: Функция отрабатывает корректно с пустым trim
  const char src[] = "*s21_string#";
  const char trim_chars[] = "";
  char expected[] = "*s21_string#";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_null_trim) {
  // - Test: Функция отрабатывает корректно с trim = NULL
  const char src[] = "Hello World";
  const char *trim_chars = NULL;
  char *actual = s21_trim(src, trim_chars);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_null_string) {
  // Test: Функция отрабатывает корректно со строкой = NULL
  const char *trim_chars = "*#";
  char *actual = s21_trim(NULL, trim_chars);

  ck_assert_ptr_null(actual);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_start) {
  // Test: Функция отрабатывает корректно с совпадениями только в начале
  const char src[] = "****s21_string";
  const char trim_chars[] = "*";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_end) {
  // Test: Функция отрабатывает корректно с совпадениями только в конце
  const char src[] = "s21_string****";
  const char trim_chars[] = "*";
  char expected[] = "s21_string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_s21_trim_middle) {
  // Test: Функция отрабатывает корректно с совпадениями посередине
  const char src[] = "s21_**string";
  const char trim_chars[] = "*";
  char expected[] = "s21_**string";
  char *actual = s21_trim(src, trim_chars);

  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

SRunner *create_runner() {
  SRunner *sr;
  Suite *s21_string;
  Suite *s21_sprintf;
  Suite *s21_sprintf_bonus;
  Suite *s21_additional_functions;
  TCase *tc_s21_memchr;
  TCase *tc_s21_memcmp;
  TCase *tc_s21_memcpy;
  TCase *tc_s21_memset;
  TCase *tc_s21_strncat;
  TCase *tc_s21_strchr;
  TCase *tc_s21_strncmp;
  TCase *tc_s21_strncpy;
  TCase *tc_s21_strcspn;
  TCase *tc_s21_strerror;
  TCase *tc_s21_strlen;
  TCase *tc_s21_strpbrk;
  TCase *tc_s21_strrchr;
  TCase *tc_s21_strstr;
  TCase *tc_s21_strtok;
  TCase *tc_sprintf_main;
  TCase *tc_sprintf_bonus;
  TCase *tc_s21_to_upper;
  TCase *tc_s21_to_lower;
  TCase *tc_s21_insert;
  TCase *tc_s21_trim;

  s21_string = suite_create("string");
  s21_sprintf = suite_create("sprintf");
  s21_sprintf_bonus = suite_create("sprintf_bonus");
  s21_additional_functions = suite_create("additional_functions");

  sr = srunner_create(s21_string);
  srunner_add_suite(sr, s21_sprintf);
  srunner_add_suite(sr, s21_sprintf_bonus);
  srunner_add_suite(sr, s21_additional_functions);

  tc_s21_memchr = tcase_create("s21_memchr");
  tcase_add_test(tc_s21_memchr, test_s21_memchr_correct);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_fb);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_lb);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_out_of_reach);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_null_term);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_invis);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_empty_str);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_char_not_exist);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_n_eq_zero);
  tcase_add_test(tc_s21_memchr, test_s21_memchr_len_greater_than_n);

  tc_s21_memcmp = tcase_create("s21_memcmp");
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_equal);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_fb_greater);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_fb_less);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_fbite);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_lbite);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_middle);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_null_term);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_invis);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_f_empty_str);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_s_empty_str);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_fs_less_than_n);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_ss_less_than_n);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_fs_greater_than_n);
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp_ss_greater_than_n);

  tc_s21_memcpy = tcase_create("s21_memcpy");
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_correct);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_arrs);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_n_eq_null);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_empty_str);

  tc_s21_memset = tcase_create("s21_memset");
  tcase_add_test(tc_s21_memset, test_s21_memset_basic);
  tcase_add_test(tc_s21_memset, test_s21_memset_array_null);
  tcase_add_test(tc_s21_memset, test_s21_memset_n_eq_zero);
  tcase_add_test(tc_s21_memset, test_s21_memset_n_eq_one);
  tcase_add_test(tc_s21_memset, test_s21_memset_n_eq_buff);
  tcase_add_test(tc_s21_memset, test_s21_memset_null_term);
  tcase_add_test(tc_s21_memset, test_s21_memset_invis);
  tcase_add_test(tc_s21_memset, test_s21_memset_n_gt_buff);

  tc_s21_strncat = tcase_create("s21_strncat");
  tcase_add_test(tc_s21_strncat, test_s21_strncat_correct_full);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_correct_part);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_n_eq_zero);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_empty_src);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_empty_dest);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_src_less_than_n);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_src_greater_than_n);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_src_null_term_add);
  tcase_add_test(tc_s21_strncat, test_s21_strncat_invis);

  tc_s21_strchr = tcase_create("s21_strchr");
  tcase_add_test(tc_s21_strchr, test_s21_strchr_correct_fs);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_correct_ls);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_correct_middle);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_empty_str);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_single_char);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_null_search);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_invis);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_registr);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_null_term_empty_str);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_symb_not_exist);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_mult_entry);
  tcase_add_test(tc_s21_strchr, test_s21_strchr_null_str);

  tc_s21_strncmp = tcase_create("s21_strncmp");
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_eq);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_second_string_greater);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_first_string_greater);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_second_string_length_greater);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_first_string_length_greater);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_n_eq_zero);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_null_term);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_invis);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_both_empty);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_first_string_empty);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_second_string_empty);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_first_string_less_than_n);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_second_string_less_than_n);
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp_registr);

  tc_s21_strncpy = tcase_create("s21_strncpy");
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_correct_full);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_correct_part);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_n_eq_zero);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_empty_str);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_null_term);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_invis);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_dest_empty);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_src_less_than_n);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_src_greater_than_n);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_src_null);
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy_dest_null);

  tc_s21_strcspn = tcase_create("s21_strcspn");
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_nonmatch);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_match);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_match_middle);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_first_string_empty);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_second_string_empty);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_both_strings_empty);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_null_term_search);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_invis);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_end_of_first_string);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_multiple_match);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_registr);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_second_string_doubles);
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn_wrong_order);

  tc_s21_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_s21_strerror, test_s21_strerror_correct);
  tcase_add_test(tc_s21_strerror, test_s21_strerror_less_then_zero);
  tcase_add_test(tc_s21_strerror, test_s21_strerror_begger_then_size);
  tcase_add_test(tc_s21_strerror, test_s21_strerror_border);

  tc_s21_strlen = tcase_create("s21_strlen");
  tcase_add_test(tc_s21_strlen, test_s21_strlen_correct_line);
  tcase_add_test(tc_s21_strlen, test_s21_strlen_empty_string);
  tcase_add_test(tc_s21_strlen, test_s21_strlen_space);
  tcase_add_test(tc_s21_strlen, test_s21_strlen_invis);
  tcase_add_test(tc_s21_strlen, test_s21_strlen_null_term);

  tc_s21_strpbrk = tcase_create("s21_strpbrk");
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_first_symbol);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_middle);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_last_symbol);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_multiple_symbols);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_not_match);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_first_empty_string);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_second_empty_string);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_both_empty_string);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_special_symbols);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_numbers);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_registr);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_first_multiple);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_second_multiple);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_unreach);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_second_whole_alph);
  tcase_add_test(tc_s21_strpbrk, test_s21_strpbrk_second_space);

  tc_s21_strrchr = tcase_create("s21_strrchr");
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_single_match);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_multiple_match);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_last_symbol);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_first_symbol);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_not_match);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_empty_string);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_null_term_search);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_special_symbol);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_registr);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_null_term);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_numbers);
  tcase_add_test(tc_s21_strrchr, test_s21_strrchr_space);

  tc_s21_strstr = tcase_create("s21_strstr");
  tcase_add_test(tc_s21_strstr, test_s21_strstr_match_at_start);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_match_in_the_middle);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_match_in_the_end);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_full_match);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_not_match);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_first_string_empty);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_second_string_empty);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_both_strings_empty);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_special_symbols);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_numbers);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_register);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_repeatable_symbols);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_overlay);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_partial);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_long_string);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_null_term);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_one_symbol);
  tcase_add_test(tc_s21_strstr, test_s21_strstr_space);

  tc_s21_strtok = tcase_create("s21_strtok");
  tcase_add_test(tc_s21_strtok, test_s21_strtok_simple);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_diff_delim);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_empty_str);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_str_of_delim);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim_first);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim_last);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim_first_and_last);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_registr);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_tabs);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_change_of_delim);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim_expand);
  tcase_add_test(tc_s21_strtok, test_s21_strtok_delim_num);

  tc_sprintf_main = tcase_create("sprintf_main");
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_char);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_l_char);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_special);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_invis);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_positive);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_negative);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_intmax);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_intmin);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_space);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_plus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_width);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_d_width_minus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_usual);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_plus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_plus_negative);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_plus_zero_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_space);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_space_negative);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_space_zero_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_zero_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_minus_zero_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_precision);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_f_precision_and_width);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_usual);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_long);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_long_null);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_empty_string);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_width);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_width_minus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_width_low_minus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_s_precision);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_usual);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_h_usual);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_l_usual);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_zero_precision);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_percent);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_percent_combined);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_positive);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_negative);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_zero);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_int_max);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_int_min);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_width);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_i_width_minus);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_width_char);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_precision_zero_for_d);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_precision_border_for_d);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_width_zero_for_d);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_u_precision);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_short_int);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_long_int);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_long_float);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_all_mods);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_all_specs);
  tcase_add_test(tc_sprintf_main, test_s21_sprintf_incorrect);

  tc_sprintf_bonus = tcase_create("sprintf_bonus");
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_float);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_x_upper);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_x_low);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_g);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_g_short);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_g_short_zero);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_s_precision_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_d_width_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_f_precision_bonus);
  tcase_add_test(tc_sprintf_bonus,
                 test_s21_sprintf_f_precision_and_width_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_s_width_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_i_width_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_negative_width_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_percent_o_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_percent_p_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_percent_p_null);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_sharp_x_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_sharp_o_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_sharp_g_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Lf_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Le_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_LE_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Lg_bonus);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Lf_bonus_inf);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Lf_bonus_minus_inf);
  tcase_add_test(tc_sprintf_bonus, test_s21_sprintf_Lf_bonus_nan);

  tc_s21_to_upper = tcase_create("s21_to_upper");
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper_usual);
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper_uppercased);
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper_empty_str);
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper_nums_chars);
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper_null);

  tc_s21_to_lower = tcase_create("s21_to_lower");
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower_usual);
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower_lowercased);
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower_empty_str);
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower_nums_chars);
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower_null);

  tc_s21_insert = tcase_create("s21_insert");
  tcase_add_test(tc_s21_insert, test_s21_insert_usual);
  tcase_add_test(tc_s21_insert, test_s21_insert_empty_into_full);
  tcase_add_test(tc_s21_insert, test_s21_insert_full_into_empty);
  tcase_add_test(tc_s21_insert, test_s21_insert_into_start);
  tcase_add_test(tc_s21_insert, test_s21_insert_into_end);
  tcase_add_test(tc_s21_insert, test_s21_insert_unreach);
  tcase_add_test(tc_s21_insert, test_s21_insert_into_null);
  tcase_add_test(tc_s21_insert, test_s21_insert_mull_into_string);

  tc_s21_trim = tcase_create("s21_trim");
  tcase_add_test(tc_s21_trim, test_s21_trim_space);
  tcase_add_test(tc_s21_trim, test_s21_trim_copies);
  tcase_add_test(tc_s21_trim, test_s21_trim_diff_symbols);
  tcase_add_test(tc_s21_trim, test_s21_trim_no_match);
  tcase_add_test(tc_s21_trim, test_s21_trim_full_trim);
  tcase_add_test(tc_s21_trim, test_s21_trim_empty_string);
  tcase_add_test(tc_s21_trim, test_s21_trim_empty_trim);
  tcase_add_test(tc_s21_trim, test_s21_trim_null_trim);
  tcase_add_test(tc_s21_trim, test_s21_trim_null_string);
  tcase_add_test(tc_s21_trim, test_s21_trim_start);
  tcase_add_test(tc_s21_trim, test_s21_trim_end);
  tcase_add_test(tc_s21_trim, test_s21_trim_middle);

  suite_add_tcase(s21_string, tc_s21_memchr);
  suite_add_tcase(s21_string, tc_s21_memcmp);
  suite_add_tcase(s21_string, tc_s21_memcpy);
  suite_add_tcase(s21_string, tc_s21_memset);
  suite_add_tcase(s21_string, tc_s21_strncat);
  suite_add_tcase(s21_string, tc_s21_strchr);
  suite_add_tcase(s21_string, tc_s21_strncmp);
  suite_add_tcase(s21_string, tc_s21_strncpy);
  suite_add_tcase(s21_string, tc_s21_strcspn);
  suite_add_tcase(s21_string, tc_s21_strlen);
  suite_add_tcase(s21_string, tc_s21_strerror);
  suite_add_tcase(s21_string, tc_s21_strpbrk);
  suite_add_tcase(s21_string, tc_s21_strrchr);
  suite_add_tcase(s21_string, tc_s21_strstr);
  suite_add_tcase(s21_string, tc_s21_strtok);

  suite_add_tcase(s21_sprintf, tc_sprintf_main);
  suite_add_tcase(s21_sprintf_bonus, tc_sprintf_bonus);
  suite_add_tcase(s21_additional_functions, tc_s21_to_upper);
  suite_add_tcase(s21_additional_functions, tc_s21_to_lower);
  suite_add_tcase(s21_additional_functions, tc_s21_insert);
  suite_add_tcase(s21_additional_functions, tc_s21_trim);

  return sr;
}

int main(void) {
  SRunner *sr = create_runner();
  srunner_run_all(sr, CK_NORMAL);
  int failed_quantity = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_quantity == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
