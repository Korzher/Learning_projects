#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep.h"

void output(Options options, char* argv[]) {
  if (options.len_pattern == 0) {
    fprintf(stderr, "No pattern specified\n");
    exit(1);
  }
  regex_t re;
  int flags = REG_EXTENDED;
  if (options.i) flags = REG_EXTENDED | REG_ICASE;
  int err = regcomp(&re, options.pattern, flags);
  if (err) {
    fprintf(stderr, "Regex error\n");
    exit(1);
  }

  for (int i = options.optind; i < options.argc; i++) {
    processFile(options, argv[i], &re);
  }
  regfree(&re);
}

void processFile(Options options, const char* path, regex_t* re) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!options.s) perror(path);
    return;
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0, line_number = 1, match_count = 0;
  while ((read = getline(&line, &memlen, f)) != -1) {
    int result = regexec(re, line, 0, NULL, 0);
    int is_match;
    if (options.v) {
      is_match = (result != 0);
    } else {
      is_match = (result == 0);
    }
    if (is_match) {
      match_count++;
      if (options.l) break;
      if (options.o && !options.c) {
        print_match(re, line, path, line_number, options);
      } else if (!options.c) {
        if (!options.h && (options.argc - options.optind > 1))
          printf("%s:", path);
        if (options.n) printf("%d:", line_number);
        output_line(line, read);
      }
    }
    line_number++;
  }
  free(line);
  fclose(f);
  if (options.l && match_count > 0) {
    printf("%s\n", path);
  } else if (options.c) {
    if (!options.h && (options.argc - options.optind > 1)) printf("%s:", path);
    printf("%d\n", match_count);
  }
}

void print_match(regex_t* re, const char* line, const char* path,
                 int line_number, Options options) {
  regmatch_t match;
  int offset = 0;
  int line_len = strlen(line);

  while (regexec(re, line + offset, 1, &match, 0) == 0) {
    int len = match.rm_eo - match.rm_so;

    if (match.rm_so != match.rm_eo) {
      if (!options.h && (options.argc - options.optind > 1)) {
        printf("%s:", path);
      }
      if (options.n) {
        printf("%d:", line_number);
      }
      printf("%.*s\n", len, line + offset + match.rm_so);
    }

    if (len == 0) {
      offset++;
      if (offset > line_len) break;
    } else {
      offset += match.rm_eo;
    }
  }
}

void output_line(const char* line, int n) {
  if (n > 0 && line[n - 1] == '\n') {
    printf("%.*s", n, line);
  } else {
    printf("%.*s", n, line);
    putchar('\n');
  }
}