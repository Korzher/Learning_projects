#include "s21_string.h"

static char *messages[] = ERROR_MESSAGES;

char *s21_strerror(int errnum) {
  int count = sizeof(messages) / sizeof(messages[0]);
  if (errnum < 0 || errnum >= count) {
    return "Unknown error";
  }
  return messages[errnum];
}
