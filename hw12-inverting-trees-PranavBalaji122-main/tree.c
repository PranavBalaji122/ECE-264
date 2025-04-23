#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Implement all the functions in tree.h here.
 *
 * Use as many helper functions as you need, just declare them to be static.
 *
 * 
 * 
 */
// static helper functions I used
static Tree *read_node(FILE*);
static void write_preorder(FILE*, Tree*);


// allocating the nodes for the tree
static Tree *alloc_node(int data) {
  Tree *ret = calloc(1, sizeof(Tree));
  if (ret == NULL) {
    return NULL;
  }

  ret->data = data;
  return ret;
}


// inverting the tree using recursion and a temp val
Tree *invert_tree(Tree *root){
  if(root == NULL){
    return NULL;
  }
    Tree *tmp = root->right;
    root->right  = invert_tree(root->left);
    root->left = invert_tree(tmp);
    return root;
}



Tree *read_from_file(char *filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }

    Tree *rt = read_node(file);
    fclose(file);
    return rt;
}


static Tree *read_node(FILE *file) {
    int value;
    //using a flag to read the nodes from the file
    unsigned char f;
  


    if (fread(&value, sizeof(value), 1, file) != 1) {
        return NULL;
    }
    if (fread(&f, sizeof(f), 1, file) != 1) {
        return NULL;
    }
    // creating new node using allocate node method

    Tree *node = alloc_node(value);
    if (f & 0x02) { 
      // if the node is 0x02 then set it to the left 
        node->left = read_node(file);
    }
    if (f & 0x01) {
      //else set it to the right
        node->right = read_node(file);
    }
    return node;
}


void preorder_print(Tree *root, char *filename){
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return;
    }

    write_preorder(file, root);


    fclose(file);

}

static void write_preorder(FILE *file, Tree *node) {
    if (node == NULL) {
        return;
    }

    int data = node->data;
    //using fwrite function to add the data to the file
    fwrite(&data, sizeof(data), 1, file);
    unsigned char f = 0;

    if (node->left != NULL) {
        f |= 0x02;
    }
    if (node->right != NULL) {
        f |= 0x01;
    }

    
    fwrite(&f, sizeof(f), 1, file);
    write_preorder(file, node->left);
    write_preorder(file, node->right);
}


// freeing tree method
void free_tree(Tree *root){
    if(root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

