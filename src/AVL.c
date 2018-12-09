#include "header.h"
#include <string.h>

Node_AVL* newNode(Data_FIX berkas)
{
    Node_AVL *new_node = (Node_AVL*)malloc(sizeof(Node_AVL));

    new_node->nik = berkas.nik;
    strcpy(new_node->casa, berkas.casa);
    strcpy(new_node->nik_casa, berkas.nik_casa);
    strcpy(new_node->casi, berkas.casi);
    strcpy(new_node->nik_casi, berkas.nik_casi);
    new_node->no_telp = berkas.no_telp;
    strcpy(new_node->alamat, berkas.alamat);
    strcpy(new_node->tgl_nikah, berkas.tgl_nikah);
    strcpy(new_node->nama_penghulu, berkas.nama_penghulu);
    strcpy(new_node->nip_penghulu, berkas.nip_penghulu);

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
    else if (berkas.nik < node->nik)
        node->left = insert(node->left, berkas);
    else if (berkas.nik > node->nik)
        node->right = insert(node->right, berkas);
    else    // Nilai sama tidak diperbolehkan di BST
        return node;

    // 2. Perbarui masing-masing height
    node->height = max(height(node->left), height(node->right)) + 1;

    //  3. Cek balance atau tidak
    int balance = get_balance(node);
    // Jika tidak balance, maka akan ada 4 pengecekan...
    if (balance > 1 && berkas.nik < node->left->nik)
    {
        // Left Left Rotation
        return right_rotate(node);
    }
    else if (balance < -1 && berkas.nik > node->right->nik)
    {
        // Right Right Rotation
        return left_rotate(node);
    }
    else if (balance > 1 && berkas.nik > node->left->nik)
    {
        // Left Right Rotation
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (balance < -1 && berkas.nik < node->right->nik)
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
Node_AVL* delete_node(Node_AVL *node, unsigned long long nik)
{
    // 1. Standard BST deletion
    if (node == NULL)
        return node;
    else if (nik < node->nik)
        node->left = delete_node(node->left, nik);
    else if (nik > node->nik)
        node->right = delete_node(node->right, nik);
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
            node->nik = temp->nik;
            // Delete the inorder successor
            node->right = delete_node(node->right, temp->nik);
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

int inorder(Node_AVL *node, int batasBawah, int *y, int batasAtas)
{
    if (node != NULL)
    {
        batasBawah = inorder(node->left, batasBawah, y, batasAtas);
        batasBawah--;
        if (0 >= batasBawah && batasBawah > batasAtas * -1) {
            gotoXY(37, *y += 2);
            printf("Penghulu\t\t: %s",node->nama_penghulu);
            gotoXY(37, ++*y);
			printf("Calon suami\t: %s",node->casa);
            gotoXY(37, ++*y);
			printf("Nip suami\t\t: %s",node->nik_casa);
            gotoXY(37, ++*y);
			printf("Calon istri\t: %s",node->casi);
            gotoXY(37, ++*y);
			printf("Nip istri\t\t: %s",node->nik_casi);
            gotoXY(37, ++*y);
			printf("Alamat\t\t: %s",node->alamat);
            gotoXY(37, ++*y);
			printf("Tanggal\t\t: %s",node->tgl_nikah);
            gotoXY(37, ++*y);
			printf("No telp\t\t: %llu",node->no_telp);
        }
        batasBawah = inorder(node->right, batasBawah, y, batasAtas);
    }
    return batasBawah;
}

void destroy_tree(Node_AVL **node)
{
    while (*node != NULL)
        *node = delete_node(*node, (*node)->nik);
}

unsigned long long convert_to_digit(const char number, unsigned long long *x)
{
	unsigned long long digit = 0;
	switch (number)
    {
        case '1':
            digit += (*x * 1);
			break;
        case '2':
            digit += (*x * 2);
			break;
        case '3':
            digit += (*x * 3);
			break;
        case '4':
            digit += (*x * 4);
			break;
        case '5':
            digit += (*x * 5);
			break;
        case '6':
            digit += (*x * 6);
			break;
        case '7':
            digit += (*x * 7);
			break;
        case '8':
            digit += (*x * 8);
			break;
        case '9':
            digit += (*x * 9);
			break;
        default:
            // Bukan karakter angka? abaikan.
            break;
    }

	*x *= 10;
	return digit;
}

unsigned long long str_to_int(const char nik_casa[11])
{
	int length = sizeof(nik_casa) / sizeof(nik_casa[0]);
	unsigned long long nik_casa_int = 0, x = 1;
    // Untuk convert tiap digit, satuan-puluhan-ratusan-.....
    for (int i = (length - 1); i >= 0; --i)
		nik_casa_int += convert_to_digit(nik_casa[i], &x);

	return nik_casa_int;
}

void waiting_list(Node_AVL **node, Data_FIX berkas)
{
    // Convert nik_casa (char array) ke integer
    berkas.nik = str_to_int(berkas.nik_casa);

    // Rangkai ke dalam tree
    *node = insert(*node, berkas);
}

int cancel(Node_AVL **node, char nik_casa[11], Node_SINGLY **head,int flag) {
	Node_AVL *temp = *node;
	unsigned long long nik_casa_int = str_to_int(nik_casa);
	if (temp != NULL) {
		if (temp->nik != nik_casa_int) {
			flag = cancel(&(temp->left), nik_casa, head, flag);
			flag = cancel(&(temp->right), nik_casa, head, flag);
		}

		if (temp->nik == nik_casa_int) {
			selesai_digunakan(head, temp->nip_penghulu);
			*node = delete_node(temp, temp->nik);
            system("CLS");
			printf("Pernikahan telah dibatalkan / selesai.");
			flag = 1;
		}
	}
    
	return flag;
}
