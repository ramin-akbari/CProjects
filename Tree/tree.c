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
    out->print = print_tree;
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

void expand_node(tree* node,array* arr, int curr_index){
    if (2*curr_index+1 >= arr->size)
        return;

    node->add_left(node,arr->index[2*curr_index+1]);

    if (2*curr_index+2 >= arr->size)
        return;

    node->add_right(node,arr->index[2*curr_index+2]);

    expand_node(node->left,arr,2*curr_index+1);
    expand_node(node->right,arr,2*curr_index+2);
}

tree* from_array(array* arr){
    if (arr->size==0)
        return NULL;
    tree* root = init_tree(arr->index[0]);
    expand_node(root,arr, 0);
    return root;
}

void print_tree(const tree* node) {
    if (node==NULL)
        return;
    print_tree(node->left);
    printf("%4d",node->data);
    print_tree(node->right);
    if(node->parent==NULL)
        printf("\n\n");
}
