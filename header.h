#ifndef HEADER
#define HEADER

// Singly Linked-list

// Queue

// AVL Tree
struct Node_AVL
{
    int value;
    int height;
    struct Node_AVL *left, *right;
};
typedef struct Node_AVL Node_AVL;

Node_AVL* insert(Node_AVL *node, int value);
Node_AVL* delete_node(Node_AVL *node, int value);
void preorder(Node_AVL *node);
Node_AVL* destroy_tree(Node_AVL *node);

#endif // HEADER
