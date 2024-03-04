#ifndef TREE_H
#define TREE_H

#include "array.h"

typedef struct tree {
 int data;
 struct tree *left;
 struct tree *right;
 struct tree *parent;
 void (*add_right) (struct tree *,int);
 void (*add_left) (struct tree *,int);
 void (*print)(const struct tree* );
} tree;

tree* init_node();
tree* init_tree(int);
void add_to_left(tree*,int);
void add_to_right(tree*, int);
tree* from_array(array* );
void print_tree(const tree* );
#endif //TREE_H
