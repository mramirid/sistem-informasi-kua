#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

// Singly Linked-list
struct Node_SINGLY
{
	char nama[30], nip[30];
	int terpakai, usia;
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
	char nama_penghulu[30], nip_penghulu[30];
	char casa[30], nik_casa[30], casi[30], nik_casi[30];
	char alamat[30], tgl_nikah[11];
    unsigned long long nik, no_telp;
    int height;
    struct Node_AVL *left, *right;
};

// TAK PAKAI INI DARIPADA PASSING BANYAK PARAMETER
struct Data_FIX
{
	char nama_penghulu[30], nip_penghulu[30];
	char casa[30], nik_casa[30], casi[30], nik_casi[30];
	char alamat[30], tgl_nikah[11];
	unsigned long nik, no_telp;
};

// Typedefs
typedef struct Node_SINGLY Node_SINGLY;
typedef struct Node_QUE Node_QUE;
typedef struct queue Queue;
typedef struct Node_AVL Node_AVL;
typedef struct Data_FIX Data_FIX;

// Functions of SINGLY
int tambah_data(Node_SINGLY **head);
void cetak(Node_SINGLY *head, int next); // Variabel next, awal data mana yang ditampilkan.
void edit(Node_SINGLY **head);
int hapus(Node_SINGLY **head);
Node_SINGLY* gunakan_pegawai(Node_SINGLY **head);
void selesai_digunakan(Node_SINGLY **head, char *nip);
void destroy_list(Node_SINGLY **head);

// Functions of QUE
Queue createQueue();
int enqueue(Queue *antrian);
Node_QUE* dequeue(Queue *antrian);
void display(Queue antrian, int batas);
void destroy_queue(Queue *antrian);

// Fuctions of AVL
Node_AVL* insert(Node_AVL *node, Data_FIX berkas);
Node_AVL* delete_node(Node_AVL *node, unsigned long long nik);
int inorder(Node_AVL *node, int batasBawah, int *y, int batasAtas);
void destroy_tree(Node_AVL **node);
// void inorder(Node_AVL *node);
void waiting_list(Node_AVL **node, Data_FIX berkas);
// int done(Node_AVL **node, Node_SINGLY **head);
int cancel(Node_AVL **node, char tanggal[11], Node_SINGLY **head);
Node_AVL* min_value_node(Node_AVL *node);

void gotoXY(int x, int y);

#endif // HEADER
