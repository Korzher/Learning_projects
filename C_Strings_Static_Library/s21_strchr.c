#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  char *result = S21_NULL;

  do {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
  } while (*str++ != '\0');

  return result;
}
