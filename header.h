#ifndef HEADER
#define HEADER

// Singly Linked-list
struct Node_SINGLY{
	char nip[20],nama[20];
	int usia;
	struct Node_SINGLY *right;
};
// Queue
struct Node_QUE{
};

// AVL Tree
struct Node_AVL
{
    int value;
    int height;
    struct Node_AVL *left, *right;
};

//typedef
typedef struct Node_SINGLY Node_SINGLY;
typedef struct Node_QUE Node_QUE;
typedef struct Node_AVL Node_AVL;


//Functions of SINGLY
void tambah_data(Node_SINGLY **head);
void cetak(Node_SINGLY* head,int next);//variabel next, awal data mana yang ditampilkan.
void edit(Node_SINGLY** head);
void hapus(Node_SINGLY** head);
//Functions of QUE

//Fuctions of AVL
Node_AVL* insert(Node_AVL *node, int value);
Node_AVL* delete_node(Node_AVL *node, int value);
void preorder(Node_AVL *node);
Node_AVL* destroy_tree(Node_AVL *node);

void gotoXY(int x, int y);
#endif // HEADER
