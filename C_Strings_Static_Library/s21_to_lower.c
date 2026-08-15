#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (!str) {
    s21_strerror(22);
    return S21_NULL;
  }

  int len = s21_strlen(str);

  char *result = malloc(len + 1);
  if (!result) {
    s21_strerror(12);
    return S21_NULL;
  }

  for (int i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }
  result[len] = '\0';
  return result;
}
