#ifndef ARRAYH
#define ARRAYH
#include <stdio.h>

typedef struct Array {
  unsigned int size;
  unsigned int capacity;
  int *index;
  void (*from_file)(struct Array *, FILE *);
  void (*add)(struct Array *, int);
  void (*free)(struct Array*);
} array;

array *init_array(void);
void read_file(array *, FILE *);
void resize(array *);
void add_element(array *, const int);
void free_array(array*);
#endif



