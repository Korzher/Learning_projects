#include <regex.h>

#ifndef GREP_H
#define GREP_H

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
  char* pattern;
  int len_pattern;
  int mem_pattern;
  int argc;
  int optind;
} Options;

Options parser(int argc, char* argv[], Options* options);
void add_reg_from_file(Options* options, const char* filepath);
void pattern_add(Options* options, const char* pattern);
void output(Options options, char* argv[]);
void processFile(Options options, const char* path, regex_t* re);
void print_match(regex_t* re, const char* line, const char* path,
                 int line_number, Options options);
void output_line(const char* line, int n);

#endif
