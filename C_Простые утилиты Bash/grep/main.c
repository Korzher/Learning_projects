#include <stdlib.h>

#include "grep.h"

int main(int argc, char* argv[]) {
  Options options = {0};
  options = parser(argc, argv, &options);
  output(options, argv);
  free(options.pattern);
  return 0;
}
