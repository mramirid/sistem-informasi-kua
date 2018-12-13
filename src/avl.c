#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "singly_ll.h"
#include "avl.h"

// Entah kenopo isok konflik karo fungsi max()
// Yawes tak undef
#undef max

void gotoXY(int x, int y);
void selesai_digunakan(Node_SINGLY **head, unsigned long long nip);

Node_AVL* newNode(Data_FIX berkas)
{
    Node_AVL *new_node = (Node_AVL*)malloc(sizeof(Node_AVL));

    strcpy(new_node->nama_penghulu, berkas.nama_penghulu);
    new_node->nip_penghulu = berkas.nip_penghulu;
    strcpy(new_node->casa, berkas.casa);
    new_node->nik_casa = berkas.nik_casa;
    strcpy(new_node->casi, berkas.casi);
    new_node->nik_casi = berkas.nik_casi;
    new_node->no_telp = berkas.no_telp;
    strcpy(new_node->alamat, berkas.alamat);
    strcpy(new_node->tgl_nikah, berkas.tgl_nikah);

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
Node_AVL* insert(Node_AVL *node, Data_FIX berkas)
{
    // 1. Standard BST insertion
    if (node == NULL)
        return newNode(berkas);
    else if (berkas.nik_casa < node->nik_casa)
        node->left = insert(node->left, berkas);
    else if (berkas.nik_casa > node->nik_casa)
        node->right = insert(node->right, berkas);
    else
        return node;

    // 2. Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;

    //  3. Cek balance atau tidak
    int balance = get_balance(node);

    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && berkas.nik_casa < node->left->nik_casa)
        return right_rotate(node);
    else if (balance < -1 && berkas.nik_casa > node->right->nik_casa)
        return left_rotate(node);
    else if (balance > 1 && berkas.nik_casa > node->left->nik_casa)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && berkas.nik_casa < node->right->nik_casa)
    {
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
Node_AVL* delete_node(Node_AVL *node, unsigned long long nik)
{
    // 1. Standard BST deletion
    if (node == NULL)
        return node;
    else if (nik < node->nik_casa)
        node->left = delete_node(node->left, nik);
    else if (nik > node->nik_casa)
        node->right = delete_node(node->right, nik);
    else    // Jika nilai yang dihapus ketemu
    {
        // Jika node ini hanya memiliki 1 child atau tidak sama sekali
        if (node->left == NULL || node->right == NULL)
        {
            // Ambil node terkecil untuk pengganti root (jika ada)
            Node_AVL *temp = node->left ? node->left : node->right;

            if (temp == NULL)
            {
                // Jika tidak punya child
                // Persiapkan untuk menghapus leaf tersebut
                temp = node;
                node = NULL;
            }
            else
            {
                // Jika punya 1 anak (left child)
                // Salin data child ke root saat ini (timbun)
                // Dan hapus child tersebut
                *node = *temp;
            }

            free(temp);
        }
        else
        {
            // Jika node ini punya 2 children,
            // Maka cari node terkecil di right subtree
            // Untuk menggantikan root subtree saat ini
            Node_AVL *temp = min_value_node(node->right);

            // Salin nilai yang telah dicari tadi ke node saat ini
            strcpy(node->nama_penghulu, temp->nama_penghulu);
            node->nip_penghulu = temp->nip_penghulu;
            strcpy(node->casa, temp->casa);
            node->nik_casa = temp->nik_casa;
            strcpy(node->casi, temp->casi);
            node->nik_casi = temp->nik_casi;
            node->no_telp = temp->no_telp;
            strcpy(node->alamat, temp->alamat);
            strcpy(node->tgl_nikah, temp->tgl_nikah);
            
            // Hapus node terkecil tadi (karena telah menggantikan root subtree saat ini)
            node->right = delete_node(node->right, temp->nik_casa);
        }
    }

    // Jika sub-tree saat ini hanya memiliki 1 node atau
    // Jika node saat ini adalah leaf yang terhapus
    if (node == NULL)
        return node;

    // 2. Update height node saat ini
    node->height = max(height(node->left), height(node->right)) + 1;

    // 3. Cek balance atau tidak
    int balance = get_balance(node);
    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && get_balance(node->left) >= 0)
        return right_rotate(node);
    else if (balance > 1 && get_balance(node->left) < 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && get_balance(node->right) <= 0)
        return left_rotate(node);
    else if (balance < -1 && get_balance(node->right) > 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

int inorder(Node_AVL *node, int batasBawah, int *y, int batasAtas)
{
    if (node != NULL)
    {
        batasBawah = inorder(node->left, batasBawah, y, batasAtas);
        batasBawah--;
        if (0 >= batasBawah && batasBawah > batasAtas * -1) {
            gotoXY(37, *y += 2);
            printf("Nama penghulu\t: %s",node->nama_penghulu);
            gotoXY(37, ++*y);
			printf("Nama calon suami\t: %s",node->casa);
            gotoXY(37, ++*y);
			printf("NIK suami\t\t: %llu",node->nik_casa);
            gotoXY(37, ++*y);
			printf("Nama calon istri\t: %s",node->casi);
            gotoXY(37, ++*y);
			printf("NIK istri\t\t: %llu",node->nik_casi);
            gotoXY(37, ++*y);
            printf("No. telp\t\t: %llu",node->no_telp);
            gotoXY(37, ++*y);
            printf("Alamat\t\t: %s",node->alamat);
            gotoXY(37, ++*y);
            printf("Tanggal\t\t: %s",node->tgl_nikah);
        }
        batasBawah = inorder(node->right, batasBawah, y, batasAtas);
    }
    return batasBawah;
}

void destroy_tree(Node_AVL **node)
{
    while (*node != NULL)
        *node = delete_node(*node, (*node)->nik_casa);
}

void waiting_list(Node_AVL **node, Data_FIX berkas)
{
    // Rangkai ke dalam tree
    *node = insert(*node, berkas);
}

int cancel(Node_AVL **node, unsigned long long nik_casa, Node_SINGLY **head, int flag) {
	Node_AVL *temp = *node;
	if (temp != NULL) {
		if (temp->nik_casa != nik_casa) {
			flag = cancel(&(temp->left), nik_casa, head, flag);
			flag = cancel(&(temp->right), nik_casa, head, flag);
		}

		if (temp->nik_casa == nik_casa) {
			selesai_digunakan(head, temp->nip_penghulu);
			*node = delete_node(temp, temp->nik_casa);
            system("CLS");
			printf("Pernikahan telah dibatalkan / selesai.");
			flag = 1;
		}
	}
    
	return flag;
}

int search(Node_AVL *node, const char tanggal_nikah[11], int flag) {
	if (node != NULL) {
		flag = search(node->left, tanggal_nikah, flag);
		if (!(strcmp(node->tgl_nikah, tanggal_nikah))) {
            printf("\nNama penghulu\t\t: %s\n",node->nama_penghulu);
			printf("Nama calon suami\t: %s\n",node->casa);
			printf("NIK suami\t\t: %llu\n",node->nik_casa);
			printf("Nama calon istri\t: %s\n",node->casi);
			printf("NIK istri\t\t: %llu\n",node->nik_casi);
            printf("No. telp\t\t: %llu\n",node->no_telp);
            printf("Alamat\t\t\t: %s\n",node->alamat);
            printf("Tanggal\t\t\t: %s\n\n",node->tgl_nikah);
            flag = 1;
		}
		flag = search(node->right, tanggal_nikah, flag);
	}

	return flag;
}
