#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (!*needle) return (char *)haystack;
  for (; *haystack; haystack++)
    if (*haystack == *needle) {
      const char *h = haystack, *n = needle;
      while (*h && *n && *h == *n) h++, n++;
      if (!*n) return (char *)haystack;
    }
  return S21_NULL;
}
