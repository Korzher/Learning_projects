#include "cat.h"

int main(int argc, char *argv[]) {
  Options options = {0};
  options = parser(argc, argv, &options);
  reader(argc, argv, options);
  return 0;
}
