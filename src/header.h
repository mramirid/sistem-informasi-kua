#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

// Singly Linked-list
struct Node_SINGLY
{
	char nip[20], nama[20];
	int usia;
	struct Node_SINGLY *right;
};

// Queue
struct Node_QUE
{
	struct Node_QUE *next, *prev;
	int nomor_antrian;
	char casa[30], nik[30];
};

struct queue
{
	int count;
	int urutan;
	struct Node_QUE *front;
	struct Node_QUE *rear;
};

// AVL Tree
struct Node_AVL
{
	char casa[30], casi[30], alamat[30], tgl_nikah[11];
    unsigned int tanggal; // FORMAT: 20181204
    int height;
    struct Node_AVL *left, *right;
};

// Typedefs
typedef struct Node_SINGLY Node_SINGLY;
typedef struct Node_QUE Node_QUE;
typedef struct queue Queue;
typedef struct Node_AVL Node_AVL;

// Functions of SINGLY
int tambah_data(Node_SINGLY **head);
void cetak(Node_SINGLY *head, int next); // Variabel next, awal data mana yang ditampilkan.
void edit(Node_SINGLY **head);
int hapus(Node_SINGLY **head);

// Functions of QUE
Queue createQueue();
int enqueue(Queue *antrian);
Node_QUE* dequeue(Queue *antrian);
void display(Queue antrian, int batas);

// Fuctions of AVL
Node_AVL* insert(Node_AVL *node, int tanggal, const char *casa, const char *casi,
                 const char *alamat, const char *tgl_nikah);
Node_AVL* delete_node(Node_AVL *node, int tanggal);
int inorder(Node_AVL *node, int batasBawah, int &y, int batasAtas);
Node_AVL* destroy_tree(Node_AVL *node);
void inorder(Node_AVL *node);
void waiting_list(Node_AVL **node, const char *casa, const char *casi, 
                  const char *alamat, const char (&tgl_nikah)[11]);

void gotoXY(int x, int y);

#endif // HEADER
