#ifndef _QUEUE_
#define _QUEUE_

struct Node_QUE
{
	struct Node_QUE *next, *prev;
	int nomor_antrian;
	char casa[30];
	unsigned long long nik_casa;
};
typedef struct Node_QUE Node_QUE;

struct Queue
{
	int count;
	int counter_urutan;
	struct Node_QUE *front;
	struct Node_QUE *rear;
};
typedef struct Queue Queue;

#endif // _QUEUE_