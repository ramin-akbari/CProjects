#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#define INITCAP 10
#define MULTIPLIER 4

void resize(array *arr) {
  arr->capacity *= MULTIPLIER;
  arr->index = (int *)realloc(arr->index, arr->capacity);
}

void add_element(array *self, const int value) {
  if (self->size == self->capacity) {
    resize(self);
  }
  self->index[(self->size++)] = value;
}

void read_file(array *self, FILE *file_ptr) {
  int temp;
  while (!feof(file_ptr)) {
    fscanf(file_ptr, "%d", &temp);
    self->add(self, temp);
  }
}

array *init_array() {
  array *out = malloc(sizeof(array));
  out->size = 0;
  out->capacity = INITCAP;
  out->index = malloc( INITCAP*sizeof(int));
  out->add = add_element;
  out->from_file = read_file;
  out->free = free_array;
  return out;
}

void free_array(array* self) {
  free(self->index);
  free(self);
}
