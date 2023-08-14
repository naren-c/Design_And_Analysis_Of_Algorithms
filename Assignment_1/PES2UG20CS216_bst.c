// Name: Naren Chandrashekhar
// SRN: PES2UG20CS216
#include "bst.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
*/

// Initializes the root of the bst
void init_bst(bst_t *bst)
{
    bst->root = NULL;
}
//Helper function to insert nodes into the BST
static node_t* insertbst(node_t *root, int key, int *count_ptr)
{
    if(root == NULL)
    {
        root = (node_t *) malloc(sizeof(node_t));
        root->key = key;
        root->left = NULL;
        root->right = NULL;
     }
    else if(key < root->key) /*Insertion in left subtree*/
        root->left = insertbst(root->left, key, ++count_ptr);
    else if(key > root->key) /*Insertion in right subtree */
        root->right = insertbst(root->right, key, ++count_ptr);

    return root;
}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr)
{
    tree->root = insertbst(tree->root, key, count_ptr);
}
//Helper function for deleteNode
static node_t* minValueNode(node_t* node)
{
    node_t* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
//Helper function to delete element
static node_t* deleteNode(node_t *root, int key, int *count_ptr)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key,++count_ptr);
 
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key,++count_ptr);
 
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            node_t* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node_t* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        node_t* temp = minValueNode(root->right);
 
        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key, count_ptr);
    }
    return root;
}
// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root = deleteNode(tree->root,key,count_ptr);
}

// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    int x = 1;
    node_t *p = tree->root;
    node_t *q = NULL;
    while (p != NULL)
    {
        q = p;
        if (p->key == key)
        {
            (*count_ptr)++;
            return p->key;
        }
        else if (key < p->key)
        {
            (*count_ptr)++;
            p = p->left;
        }
        else
            p = p->right;
    }
    return -1;
}
//Helper function to find max value
static int maxValue(node_t* node)
{
    if (node->right == NULL)
        return node->key;
    return maxValue(node->right);
}
 
// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    if(tree->root != NULL)
        return maxValue(tree->root);
    else 
        return -1;
}
//Helper function for free_bst. To free all nodes of the BST
static node_t * freenodes(node_t * node)
{
    if(node == NULL)
        return NULL;
    freenodes(node->right);
    freenodes(node->left);
    free(node);
}

// Deletes all the elements of the bst
void free_bst(bst_t *bst) 
{
    if(bst->root != NULL)
    {
        freenodes(bst->root);
        bst->root = NULL;
    }
    bst_t temp;
    init_bst(&temp);
    bst = &temp;
}
// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    if(bst->root != NULL)
    {
        freenodes(bst->root);
        bst->root = NULL;
    }
    bst_t temp;
    init_bst(&temp);
    bst = &temp;
}
