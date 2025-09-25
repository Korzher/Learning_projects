#ifndef CAT_H
#define CAT_H

typedef struct {
  int b, e, n, s, v, t;
} Options;

Options parser(int argc, char *argv[], Options *options);
void reader(int argc, char *argv[], Options options);
void outline(Options options, char *line, int n);
char v_output(char ch);

#endif
