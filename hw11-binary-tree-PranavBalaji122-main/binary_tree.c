#include "binary_tree.h"

// ***
// *** Modify this file
// ***

// The function `createNode` dynamically allocates memory for a new binary tree node and initializes its value.
// It returns a pointer to the newly created node.
TreeNode* createNode(int data) {
    // Allocate memory for a new TreeNode
    TreeNode *node = malloc(sizeof(TreeNode));
    // Check if the allocation was successful
    if(node == NULL){
        return NULL;
    }
    // Initialize the node's data and set its left and right children to NULL
    node->data = data;
    node->left = NULL;
    node->right = NULL;


    // Return the pointer to the new node
    return node;
}

// This is a warmup exercise.
// In-order traversal visits the left subtree, then the current node, and finally the right subtree.
// The function `inorderTraversal` prints the data of each node in the tree in in-order.
void inorderTraversal(TreeNode* root) {
    if(root != NULL){
        inorderTraversal(root->left);
        printf("%d\n", root->data);
        inorderTraversal(root->right);
    }
        
}

// This is a warmup exercise.
// Pre-order traversal visits the current node, then the left subtree, and finally the right subtree.
// The function `preorderTraversal` prints the data of each node in the tree in pre-order.
void preorderTraversal(TreeNode* root) {
    if(root == NULL){
        return;
    }
    printf("%d\n", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// The function `freeTree` frees the memory allocated for the binary tree.
// It recursively frees the left and right subtrees and then frees the current node.
// Step 1: if the root is NULL, return.
// Step 2: recursively free the left and right subtrees.
// Step 3: free the current node.
void freeTree(TreeNode* root) {
    if(root == NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// The function `createTree` creates a binary tree from an array representation.
// Hint: You can create a helper function to recursively build the tree.
// Step 1: base case, return NULL. What is the base case?
// Step 2: create a new node.
// Step 3: recursively create the left and right subtrees.
// Step 4: return the created node.
TreeNode* createTree(int* arr, int size) {
    if(size <=0){
        return NULL;
    }
    return(createTreeHelper(arr, size, 0));
}

TreeNode *createTreeHelper(int *arr, int size, int index){
    if(index >= size || arr[index] == -1){
        return NULL;
    }
    
    TreeNode *root = createNode(arr[index]);
    root->left = createTreeHelper(arr, size, 2*index+1);
    root->right = createTreeHelper(arr, size, 2*index+2);
    return(root);
}





// trimTree function:
// Given a binary tree where each node contains a non-negative integer and two integers, `low` and `high`, 
// your task is to trim the tree such that every root-to-leaf path in the resulting tree has a sum within the inclusive range [low, high]. 
// Specifically, any *leaf* node whose path sum from the root to that leaf falls outside this range should be removed from the tree. 
// If removing a leaf node causes its parent to become a leaf and its new path sum also falls outside the valid range, that parent should be removed as well. 
// This process should continue recursively until all remaining root-to-leaf paths satisfy the constraint.
// The structure of the remaining nodes must be preserved, and the final tree must still be a valid binary tree. 
// Your function should return the root of the trimmed tree.


TreeNode *trim_tree_helper(TreeNode *root, int sum, int low, int high){
   
    if(!root){
        return NULL;
    }
    // Adding the sum from the current node
    sum += root->data;


    root->left = trim_tree_helper(root->left, sum, low, high);
    root->right = trim_tree_helper(root->right, sum, low, high);

    // sum out of range
    if ((sum < low || sum > high) && !root->left && !root->right) {
        // free root
        free(root);
        return NULL;
    }

    return root;
}
TreeNode* trimTree(TreeNode* root, int low, int high) {
    // Hint 1: You need to keep track of the sum of the path from the root to the current node. You can do this by creating a helper function.
    // Hint 2: In your helper function, check if the current node is a leaf node. If it is, check if the sum of the path from the root to this leaf node is within the range [low, high].
    // Hint 3: When you remove a node, do not forget to free the memory allocated for that node.
    
    return trim_tree_helper(root, 0, low, high);
}

// The function `toBST` converts a binary tree into a binary search tree (BST) by pruning subtrees that violate BST properties. 
// The transformation must ensure that for every node:
// - All nodes in the left subtree have values less than the current node.
// - All nodes in the right subtree have values greater than the current node.
// **Restrictions**: The root node must remain unchanged. If a node's value violates BST properties relative to all its ancestors, its entire subtree is removed.



TreeNode* bstHelper(TreeNode *root, int min, int max){
    
    if (root == NULL) return NULL;


    if (root->data <= min || root->data >= max) {
        freeTree(root);
        return NULL;
    }


    root->left  = bstHelper(root->left,  min, root->data);
    root->right = bstHelper(root->right, root->data, max);

    return root;
}
TreeNode* toBST(TreeNode* root) {
    // Hint1: You need to keep track of the minimum and maximum values allowed for each node in the tree. You can do this by creating a helper function.
    // Hint2: In your helper function, check if the current node's value is within the valid range. If it is not, remove the subtree rooted at this node.
    // Hint3: When you remove a node, do not forget to free the memory allocated for that subtree.
    if (root == NULL){
        return NULL;    
    } 

    root->left  = bstHelper(root->left,  INT_MIN, root->data);
    root->right = bstHelper(root->right, root->data, INT_MAX);

    return root;
}
