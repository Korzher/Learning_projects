#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat.h"

void reader(int argc, char* argv[], Options options) {
  for (int i = optind; i < argc; i++) {
    FILE* f = fopen(argv[i], "r");
    if (!f) {
      perror("fopen");
      exit(1);
    }
    char* line = NULL;
    size_t memline = 0;
    int read = 0;

    int line_count = 1;
    int empty_count = 0;

    while ((read = getline(&line, &memline, f)) != -1) {
      if (options.s) {
        if (line[0] == '\n') {
          empty_count++;
          if (empty_count > 1) {
            continue;
          }
        } else {
          empty_count = 0;
        }
      }

      if (options.b) {
        if (line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count++;
        }
      } else if (options.n) {
        printf("%6d\t", line_count);
        line_count++;
      }
      outline(options, line, read);
    }
    free(line);
    fclose(f);
  }
}

void outline(Options options, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (options.t && line[i] == '\t') {
      putchar('^');
      putchar('I');
      continue;
    }
    if (options.e && line[i] == '\n') {
      putchar('$');
    }
    if (options.v) {
      line[i] = v_output(line[i]);
    }
    putchar(line[i]);
  }
}

char v_output(char ch) {
  unsigned char uch = (unsigned char)ch;

  if (uch == '\n' || uch == '\t') return ch;

  if (uch <= 31) {
    putchar('^');
    uch += 64;
  } else if (uch == 127) {
    putchar('^');
    uch = '?';
  } else if (uch > 127 && uch < 160) {
    printf("M-^");
    uch -= 64;
  } else if (uch >= 160) {
    printf("M-");
    uch -= 128;
  }
  return uch;
}
