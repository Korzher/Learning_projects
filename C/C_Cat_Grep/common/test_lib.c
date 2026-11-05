#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* run_command(const char* cmd) {
  FILE* fp = popen(cmd, "r");
  if (!fp) return NULL;

  char buffer[4096];
  char* result = malloc(4096);
  if (!result) {
    pclose(fp);
    return NULL;
  }
  result[0] = '\0';

  while (fgets(buffer, sizeof(buffer), fp)) {
    strcat(result, buffer);
  }

  pclose(fp);
  return result;
}