#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

// Singly Linked-list
struct Node_SINGLY
{
	char nip[20],nama[20];
	int usia;
	struct Node_SINGLY *right;
};

// Queue
struct Node_QUE
{
	struct Node_QUE *next, *prev;
	int nomor_antrian;
	char casa[100], casi[100], alamat[100], tgl_nikah[100], lengkapdata[10];
};

struct queue
{
	int count;
	struct Node_QUE *front;
	struct Node_QUE *rear;
};

// AVL Tree
struct Node_AVL
{
	char casa[100], casi[100], alamat[100], tgl_nikah[100], lengkapdata[10];
    int tanggal; // FORMAT: 20181204
    int height;
    struct Node_AVL *left, *right;
};

// Typedefs
typedef struct Node_SINGLY Node_SINGLY;
typedef struct Node_QUE Node_QUE;
typedef struct queue Queue;
typedef struct Node_AVL Node_AVL;

// Functions of SINGLY
void tambah_data(Node_SINGLY **head);
void cetak(Node_SINGLY* head,int next);//variabel next, awal data mana yang ditampilkan.
void edit(Node_SINGLY** head);
void hapus(Node_SINGLY** head);

// Functions of QUE
Queue createQueue();
void enqueue(Queue *antrian);
Node_QUE* dequeue(Queue *antrian);
void display(Queue antrian,int batas);

// Fuctions of AVL
Node_AVL* insert(Node_AVL *node, int tanggal, const char *casa, const char *casi,
                 const char *alamat, const char *tgl_nikah);
Node_AVL* delete_node(Node_AVL *node, int tanggal);
int inorder(Node_AVL *node, int batasBawah, int &y, int batasAtas);
Node_AVL* destroy_tree(Node_AVL *node);
void inorder(Node_AVL *node);

void gotoXY(int x, int y);

#endif // HEADER
