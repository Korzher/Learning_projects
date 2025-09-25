#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep.h"

Options parser(int argc, char* argv[], Options* options) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        pattern_add(options, optarg);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        add_reg_from_file(options, optarg);
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        fprintf(stderr, "template: ./s21_grep [e:ivclnhsf:o] [file]\n");
        exit(1);
    }
  }
  options->optind = optind;
  options->argc = argc;

  if (options->len_pattern == 0 && optind < argc) {
    pattern_add(options, argv[optind]);
    options->optind++;
  }

  if (!(options->argc - options->optind > 1)) {
    options->h = 0;
  }
  return *options;
}

void pattern_add(Options* options, const char* pattern) {
  int n = strlen(pattern);
  if (options->len_pattern == 0) {
    options->pattern = malloc(1024);
    if (!options->pattern) {
      perror("malloc");
      exit(1);
    }
    options->pattern[0] = '\0';
    options->mem_pattern = 1024;
  }

  if (options->mem_pattern < options->len_pattern + n + 4) {
    while (options->mem_pattern < options->len_pattern + n + 4) {
      options->mem_pattern *= 2;
    }
    char* new_pattern = realloc(options->pattern, options->mem_pattern);
    if (!new_pattern) {
      perror("realloc");
      free(options->pattern);
      exit(1);
    }
    options->pattern = new_pattern;
  }

  if (options->len_pattern != 0) {
    strcat(options->pattern, "|");
    options->len_pattern++;
  }

  int written =
      snprintf(options->pattern + options->len_pattern,
               options->mem_pattern - options->len_pattern, "(%s)", pattern);
  options->len_pattern += written;
}

void add_reg_from_file(Options* options, const char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!options->s) {
      perror(filepath);
    }
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read;
  while ((read = getline(&line, &memlen, f)) != -1) {
    if (read > 0 && line[read - 1] == '\n') line[read - 1] = '\0';
    if (*line) pattern_add(options, line);
  }
  free(line);
  fclose(f);
}