typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
    struct tree *parent;    
    void (*add_right) (tree*,int);
    void (*add_left) (tree*,int);
    void (*remove) (tree*);
} tree;

tree* init_tree();
void add_to_left(tree*,int);
void add_to_right(tree*, int);
void delete_node(tree*);