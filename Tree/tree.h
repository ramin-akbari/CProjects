#ifndef TREE_H
#define TREE_H

typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
    struct tree *parent;    
    void (*add_right) (struct tree *,int);
    void (*add_left) (struct tree *,int);
} tree;

tree* init_node();
tree* init_tree(int);
void add_to_left(tree*,int);
void add_to_right(tree*, int);

#endif