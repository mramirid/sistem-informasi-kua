#include "header.h"
#include <conio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

bool isEmpty(Queue antrian);

Queue createQueue()
{
	Queue antrian;
	antrian.count = 0;
	antrian.front = NULL;
	antrian.rear = NULL;

	return antrian;
}

bool isEmpty(Queue antrian)
{
	return antrian.count == 0 ? true : false;
}

int enqueue(Queue *antrian)
{
	if (antrian->count == MAX){
		printf("Maaf, Mas/Mbk pendaftaran sudah penuh!");
		return 0;	
	}
	else
	{
		Node_QUE *new_node = (Node_QUE *)malloc(sizeof(Node_QUE));
		new_node->next = NULL;

		printf("Nomor Antrian\t: %d", antrian->urutan);
		new_node->nomor_antrian = antrian->urutan++;
		fflush(stdin);
		printf("Calon suami\t: ");
		scanf("%[^\n]%*c", &(new_node->casa));
		printf("Calon istri\t: ");
		scanf("%[^\n]%*c",&(new_node->casi));
		printf("Alamat\t: ");
		scanf("%[^\n]%*c", &(new_node->alamat));
		printf("Tanggal Nikah\t: ");
		scanf("%s", &(new_node->tgl_nikah));
		printf("Data Lengkap\t: ");
		scanf("%s", &(new_node->lengkapdata));

		if (isEmpty(*antrian))
		{
			antrian->front = new_node;
			antrian->rear = new_node;
			new_node->prev=NULL;
		}
		else
		{
			antrian->rear->next = new_node;
			new_node->prev=antrian->rear;
			antrian->rear = new_node;
		}

		printf("\nData berhasil dimasukan.");
		antrian->count++;
		return 1;
	}
}

void display(Queue antrian,int batas)
{
	int x=34,y=0;
	Node_QUE *current = antrian.front;
	if(current != NULL){
		for(;batas>1;batas--)
			current=current->next;
		while (current != NULL && batas <= 3){
				gotoXY(x,y+=2);
				printf("Nomor Antrian : %d", current->nomor_antrian);
				gotoXY(x,++y);
				printf("Casa          : %s", current->casa);
				gotoXY(x,++y);
				printf("Casi          : %s", current->casi);
				gotoXY(x,++y);
				printf("Alamat        : %s", current->alamat);
				gotoXY(x,++y);
				printf("Tanggal Nikah : %s", current->tgl_nikah);
				gotoXY(x,++y);
				printf("Data Lengkap  : %s", current->lengkapdata);
				current = current->next;
				batas++;
		}
	}
	else{
		gotoXY(x,y+=2);
		printf("DATA KOSONG");
	}
}

Node_QUE* dequeue(Queue *antrian)
{
	Node_QUE *pCur, *next;

	if (isEmpty(*antrian))
		return NULL;
	else{
		printf("Data Antrian Awal Telah Dihapus!!");
		Node_QUE *first_node = antrian->front;
		antrian->front = first_node->next;

		if (antrian->count == 1)
			antrian->rear = NULL;

		Node_QUE *temp = first_node;
		free(first_node);
		antrian->count--;
		return temp;
	}
}
