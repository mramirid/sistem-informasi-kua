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

void enqueue(Queue *antrian)
{
	if (antrian->count == MAX)
		printf("Maaf, Mas/Mbk pendaftaran sudah penuh!");
	else
	{
		int nomor_antrian;
		char casa[50];
		char casi[50];
		char alamat[100];
		char tgl_nikah[10];
		char lengkapdata[5];

		printf("Nomor Antrian :");
		scanf("%d", &nomor_antrian);
		printf("Casa          :");
		scanf("%s", &casa);
		printf("Casi          :");
		scanf("%s",&casi);
		printf("Alamat        :");
		scanf("%s", &alamat);
		printf("Tanggal Nikah :");
		scanf("%s", &tgl_nikah);
		printf("Data Lengkap  :");
		scanf("%s", &lengkapdata);
		fflush(stdin);

		Node_QUE *new_node = (Node_QUE *)malloc(sizeof(Node_QUE));
		new_node -> nomor_antrian = nomor_antrian;
		strcpy(new_node -> casa, casa);
		strcpy(new_node -> casi, casi);
		strcpy(new_node -> alamat, alamat);
		strcpy(new_node -> tgl_nikah, tgl_nikah);
		strcpy(new_node -> lengkapdata, lengkapdata);
		new_node->next = NULL;
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

		antrian->count++;
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
