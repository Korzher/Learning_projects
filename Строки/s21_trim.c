#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    s21_strerror(22);
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(src);
  char *result = malloc(len + 1);
  if (!result) {
    s21_strerror(12);
    return S21_NULL;
  }

  const char *end = src + len;
  while (end > src && s21_strchr(trim_chars, *(end - 1))) {
    end--;
  }

  const char *begin = src;
  while (begin < end && s21_strchr(trim_chars, *begin)) {
    begin++;
  }

  s21_size_t new_len = end - begin;
  for (s21_size_t i = 0; i < new_len; i++) {
    result[i] = begin[i];
  }
  result[new_len] = '\0';

  return result;
}
