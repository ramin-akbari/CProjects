#include "ramin.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  ramin *a = init_ramin(integer);

  void *out = a->get(a);

  if (a->type) {
    printf("%d \n", *(int *)out);
  } else {
    printf("%s \n", (char *)out);
  }

  return 0;
}
