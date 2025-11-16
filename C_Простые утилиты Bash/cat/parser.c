#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat.h"

Options parser(int argc, char *argv[], Options *options) {
  int opt;
  struct option long_options[] = {{"number", 0, 0, 'n'},
                                  {"number-nonblank", 0, 0, 'b'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "benstvTE", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        fprintf(stderr, "template: ./s21_cat [benstvTE] [file]\n");
        exit(1);
    }
  }
  return *options;
}