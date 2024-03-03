#include "array.h"
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char **argv) {

  if (argc != 2) {
    puts("Enter address of file\n");
    return EXIT_FAILURE;
  }
  array *a = init_array();
  FILE *file = fopen(argv[1], "r");
  a->from_file(a, file);
  for (int i = 0; i < a->size; ++i) {
    printf("%d\n", a->index[i]);
  }

  return 0;
}
