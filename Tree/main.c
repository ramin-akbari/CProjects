#include "array.h"
#include "tree.h"

int main(void) {
    array* arr = init_array();
    FILE* file = fopen("data.txt","r");
    arr->from_file(arr,file);
    fclose(file);
    tree* test_tree = from_array(arr);
    test_tree->print(test_tree);
    return 0;
}
