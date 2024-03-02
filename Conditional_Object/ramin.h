
typedef enum { string, integer } datatype;

typedef struct RAMIN {
  datatype type;
  union VALUE {
    int i;
    char string[20];
  } val;

  void (*set)(datatype, struct RAMIN *self);
  void *(*get)(struct RAMIN *self);
} ramin;

void set_value(datatype, ramin *);

void *get_value(ramin *);

ramin *init_ramin(datatype);
