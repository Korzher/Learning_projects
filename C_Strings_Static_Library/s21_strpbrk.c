#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1)
    if (s21_strchr(str2, *str1++)) return (char *)(str1 - 1);
  return S21_NULL;
}
