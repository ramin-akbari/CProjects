#include "tree.h"
#include <stdlib.h>

tree* init_node(){
    tree* out = malloc(sizeof(tree));
    out->data = 0;
    out->parent = NULL;
    out->left = NULL;
    out->right = NULL;
    out->add_left = add_to_left;
    out->add_right = add_to_right;
    return out;
}

void add_to_left(tree* parent, int value){
    tree* left = init_node();
    left->data = value;
    left->parent = parent;
    parent->left = left;
}

void add_to_right(tree* parent, int value){
    tree* right = init_node();
    right->data = value;
    right->parent = parent;
    parent->right = right;
}

tree* init_tree(int value){
    tree* root = init_node();
    root->data = value;
    return root;
}
