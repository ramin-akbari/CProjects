#include "ramin.h"
#include <stdlib.h>
#include <string.h>

void set_value(datatype type, ramin *value) {
  value->type = type;
  if (value->type == integer) {
    value->val.i = 20;
    return;
  }
  strcpy(value->val.string, "C Programming");
}

void *get_value(ramin *value) {
  if (value->type == integer) {
    return &(value->val.i);
  }
  return &(value->val.string);
}

ramin *init_ramin(datatype type) {
  ramin *obj = malloc(sizeof(ramin));
  obj->set = set_value;
  obj->get = get_value;
  obj->set(type, obj);

  return obj;
}
