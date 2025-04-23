#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) { 
      
     if (argc != 3) {
        return EXIT_FAILURE;
    }
    Tree *root = read_from_file(argv[1]);
    invert_tree(root);
    preorder_print(root, argv[2]);
    free_tree(root);
    return EXIT_SUCCESS;
    
}
