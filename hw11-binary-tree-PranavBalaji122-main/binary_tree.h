#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ***
// *** Modify this file
// ***
// Add your helper functions here.

TreeNode* createNode(int data);
TreeNode* createTree(int* arr, int size);
void inorderTraversal(TreeNode* root);
void preorderTraversal(TreeNode* root);
void freeTree(TreeNode* root);
TreeNode* trimTree(TreeNode* root, int low, int high);
TreeNode* toBST(TreeNode* root);
TreeNode* bstHelper(TreeNode *root, int min, int max);
TreeNode *createTreeHelper(int *arr, int size, int index);
TreeNode *trim_tree_helper(TreeNode *root, int sum, int low, int high);

#endif // BINARY_TREE_H
