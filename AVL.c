#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node_AVL* create_node(int value)
{
    Node_AVL *new_node = (Node_AVL*)malloc(sizeof(Node_AVL));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    // Sebagai leaf node pada awalnya height bernilai 1
    new_node->height = 1;
    return new_node;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int height(Node_AVL *node)
{
    if (node == NULL)
        return 0;
    else
        return node->height;
}

int get_balance(Node_AVL *node)
{
    if (node == NULL)
        return 0;
    else
        return height(node->left) - height(node->right);
}

Node_AVL* right_rotate(Node_AVL *node)
{
    Node_AVL *new_root = node->left;
    Node_AVL *temp = new_root->right;

    // Rotation
    new_root->right = node;
    node->left = temp;

    // Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    // Return new root
    return new_root;
}

Node_AVL* left_rotate(Node_AVL *node)
{
    Node_AVL *new_root = node->right;
    Node_AVL *temp = new_root->left;

    // Rotation
    new_root->left = node;
    node->right = temp;

    // Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    // Return new root
    return new_root;
}

// Fungsi rekursif untuk insert node
Node_AVL* insert(Node_AVL *node, int value)
{
    // 1. Standard BST insertion
    if (node == NULL)
        return create_node(value);
    else if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else    // Nilai sama tidak diperbolehkan di BST
        return node;

    // 2. Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;

    //  3. Cek balance atau tidak
    int balance = get_balance(node);
    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && value < node->left->value)
    {
        // Left Left Rotation
        return right_rotate(node);
    }
    else if (balance < -1 && value > node->right->value)
    {
        // Right Right Rotation
        return left_rotate(node);
    }
    else if (balance > 1 && value > node->left->value)
    {
        // Left Right Rotation
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && value < node->right->value)
    {
        // Right Left Rotation
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    // Tidak ada rotation
    return node;
}

Node_AVL* min_value_node(Node_AVL *node)
{
    // Kiri teros
    Node_AVL *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Fungsi rekursif untuk delete node
Node_AVL* delete_node(Node_AVL *node, int value)
{
    // 1. Standard BST deletion
    if (node == NULL)
        return node;
    else if (value < node->value)
        node->left = delete_node(node->left, value);
    else if (value > node->value)
        node->right = delete_node(node->right, value);
    else    // Jika nilai yang dihapus ketemu
    {
        // Jika node ini hanya memiliki 1 child atau tidak sama sekali
        if (node->left == NULL || node->right == NULL)
        {
            Node_AVL *temp = node->left ? node->left : node->right;
            // Jika tidak punya child
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {
                // Jika punya 1 anak
                *node = *temp;
            }

            free(temp);
        }
        else
        {
            // Jika node ini punya 2 children,
            // maka cari node terkecil di right subtree
            Node_AVL *temp = min_value_node(node->right);
            // Salin nilai yang telah dicari tadi ke node saat ini
            node->value = temp->value;
            // Delete the inorder successor
            node->right = delete_node(node->right, temp->value);
        }
    }

    // Jika tree hanya memiliki 1 node
    if (node == NULL)
        return node;

    // 2. Update height node saat ini
    node->height = max(height(node->left), height(node->right)) + 1;

    // 3. Cek balance atau tidak
    int balance = get_balance(node);
    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && get_balance(node->left) >= 0)
    {
        // Left Left Rotation
        return right_rotate(node);
    }
    else if (balance > 1 && get_balance(node->left) < 0)
    {
        // Left Right Rotation
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && get_balance(node->right) <= 0)
    {
        // Right Right Rotation
        return left_rotate(node);
    }
    else if (balance < -1 && get_balance(node->right) > 0)
    {
        // Right Left Rotation
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void preorder(Node_AVL *node)
{
    if (node != NULL)
    {
        printf("%d ", node->value);
        preorder(node->left);
        preorder(node->right);
    }
}

Node_AVL* destroy_tree(Node_AVL *node)
{
    while (node != NULL)
    {
        printf("\nRoot value: %d\n", node->value);
        node = delete_node(node, node->value);
    }

    return node;
}
