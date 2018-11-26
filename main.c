#include "header.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    Node_AVL *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal setelah insertion: ");
    preorder(root);

    root = delete_node(root, 10);
    printf("\nPreorder traversal setelah penghapusan nilai 10: ");
    preorder(root);

    root = destroy_tree(root);
    printf("\nPreorder traversal setelah Deletion: ");
    preorder(root);

    printf("\nRoot value: %d\n", root);

    return 0;
}

