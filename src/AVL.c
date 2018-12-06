#include "header.h"
#include <string.h>

Node_AVL* newNode(int tanggal, const char *casa, const char *casi,
                 const char *alamat, const char *tgl_nikah)
{
    Node_AVL *new_node = (Node_AVL*)malloc(sizeof(Node_AVL));

    new_node->tanggal = tanggal;
    strcpy(new_node->casa, casa);
    strcpy(new_node->casi, casi);
    strcpy(new_node->alamat, alamat);
    strcpy(new_node->tgl_nikah, tgl_nikah);

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
Node_AVL* insert(Node_AVL *node, int tanggal, const char *casa, const char *casi,
                 const char *alamat, const char *tgl_nikah)
{
    // 1. Standard BST insertion
    if (node == NULL)
        return newNode(tanggal, casa, casi, alamat, tgl_nikah);
    else if (tanggal < node->tanggal)
        node->left = insert(node->left, tanggal, casa, casi, alamat, tgl_nikah);
    else if (tanggal > node->tanggal)
        node->right = insert(node->right, tanggal, casa, casi, alamat, tgl_nikah);
    else    // Nilai sama tidak diperbolehkan di BST
        return node;

    // 2. Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;

    //  3. Cek balance atau tidak
    int balance = get_balance(node);
    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && tanggal < node->left->tanggal)
    {
        // Left Left Rotation
        return right_rotate(node);
    }
    else if (balance < -1 && tanggal > node->right->tanggal)
    {
        // Right Right Rotation
        return left_rotate(node);
    }
    else if (balance > 1 && tanggal > node->left->tanggal)
    {
        // Left Right Rotation
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && tanggal < node->right->tanggal)
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
Node_AVL* delete_node(Node_AVL *node, int tanggal)
{
    // 1. Standard BST deletion
    if (node == NULL)
        return node;
    else if (tanggal < node->tanggal)
        node->left = delete_node(node->left, tanggal);
    else if (tanggal > node->tanggal)
        node->right = delete_node(node->right, tanggal);
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
            node->tanggal = temp->tanggal;
            // Delete the inorder successor
            node->right = delete_node(node->right, temp->tanggal);
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

int inorder(Node_AVL *node, int batasBawah, int &y, int batasAtas)
{
    if (node != NULL)
    {
        batasBawah=inorder(node->left, batasBawah,y,batasAtas);
        batasBawah--;
        if(0 >=batasBawah && batasBawah > batasAtas*-1){
            gotoXY(37,y+=2);
            printf("%d",node->tanggal);
        }
        batasBawah=inorder(node->right,batasBawah,y,batasAtas);
    }
    return batasBawah;
}

void inorder(Node_AVL *node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%u\n", node->tanggal);
        inorder(node->right);
    }
}

Node_AVL* destroy_tree(Node_AVL *node)
{
    while (node != NULL)
    {
        printf("\nRoot tanggal: %d\n", node->tanggal);
        node = delete_node(node, node->tanggal);
    }

    return node;
}

unsigned int convert_to_digit(const char number, unsigned int &x)
{
	// Untuk convert tiap digit, satuan-puluhan-ratusan-.....
	unsigned int digit = 0;
	switch (number)
    {
        case '0':
            digit += x * 0;
			break;
        case '1':
            digit += x * 1;
			break;
        case '2':
            digit += x * 2;
			break;
        case '3':
            digit += x * 3;
			break;
        case '4':
            digit += x * 4;
			break;
        case '5':
            digit += x * 5;
			break;
        case '6':
            digit += x * 6;
			break;
        case '7':
            digit += x * 7;
			break;
        case '8':
            digit += x * 8;
			break;
        case '9':
            digit += x * 9;
			break;
        default:
            break;
    }

	x *= 10;
	return digit;
}

unsigned int str_to_int(const char (&tgl_str)[11])
{
	// Convert tiap digit, abaikan karakter '-'
	// Misal 24-03-1999 dengan indeks urut dari 0
	unsigned int tgl_int = 0, x = 1;
	tgl_int += convert_to_digit(tgl_str[1], x);	// 4
	tgl_int += convert_to_digit(tgl_str[0], x);	// 2
	tgl_int += convert_to_digit(tgl_str[4], x);	// 3
	tgl_int += convert_to_digit(tgl_str[3], x);	// 0
	tgl_int += convert_to_digit(tgl_str[9], x);	// 9
	tgl_int += convert_to_digit(tgl_str[8], x);	// 9
	tgl_int += convert_to_digit(tgl_str[7], x);	// 9
	tgl_int += convert_to_digit(tgl_str[6], x);	// 1
	
	return tgl_int;
}

void waiting_list(Node_AVL **node, const char *casa, const char *casi, 
                    const char *alamat, const char (&tgl_nikah)[11])
{
    // Convert tanggal nikah (char array) ke integer
    // Format kembalian: TahunBulanTanggal
    unsigned int tanggal = str_to_int(tgl_nikah);

    // Rangkai ke dalam tree
    *node = insert(*node, tanggal, casa, casi, alamat, tgl_nikah);
}
