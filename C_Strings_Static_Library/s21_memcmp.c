#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = str1, *s2 = str2;
  while (n-- > 0) {
    if (*s1++ != *s2++) return s1[-1] - s2[-1];
  }
  return 0;
}
