#include "header.h"
#include <conio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

Queue createQueue()
{
	Queue antrian;
	antrian.count = 0;
	antrian.urutan = 1;
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
	Node_QUE *temp = antrian->front;
	int flag=1;
	if (antrian->count == MAX)
		printf("Maaf, antrian pendaftaran sudah penuh!");
	else
	{
		Node_QUE *new_node = (Node_QUE *)malloc(sizeof(Node_QUE));
		new_node->next = NULL;

		printf("Nomor Antrian\t\t: %d\n", antrian->urutan);
		new_node->nomor_antrian = antrian->urutan++;
		fflush(stdin);
		printf("Pemohon (calon suami)\t: ");
		scanf("%[^\n]%*c", &(new_node->casa));
		printf("NIK Pemohon\t\t: ");
		scanf("%s",&(new_node->nik));
		
		while (temp != NULL){
			if ( !(strcmp(temp->nik,new_node->nik)) ){
				flag=0;
				break;
			}
			temp=temp->next;
		}
		if(flag){
			if (isEmpty(*antrian))
			{
				antrian->front = new_node;
				antrian->rear = new_node;
				new_node->prev = NULL;
			}
			else
			{
				antrian->rear->next = new_node;
				new_node->prev = antrian->rear;
				antrian->rear = new_node;
			}
	
			printf("\nData berhasil dimasukan.");
			antrian->count++;	
		}
		else{
			printf("NIK tidak boleh sama");
			antrian->urutan--;
		}
	}
}

void display(Queue antrian, int batas)
{
	int x = 34, y = 0;
	Node_QUE *current = antrian.front;
	if (current != NULL) {
		for(;batas>1;batas--)
			current = current->next;
		while (current != NULL && batas <= 6) {
				gotoXY(x,y+=2);
				printf("Nomor antrian\t\t\t: %d", current->nomor_antrian);
				gotoXY(x,++y);
				printf("Nama pemohon (calon suami)\t: %s", current->casa);
				gotoXY(x,++y);
				printf("NIK Pemohon\t\t\t: %s", current->nik);
				current = current->next;
				batas++;
		}
	}
	else{
		gotoXY(x, y += 2);
		printf("DATA KOSONG");
	}
}

Node_QUE* dequeue(Queue *antrian)
{
	Node_QUE *pCur, *next;

	if (isEmpty(*antrian))
		return NULL;
	else {
		Node_QUE *first_node = antrian->front;
		antrian->front = first_node->next;

		if (antrian->count == 1)
			antrian->rear = NULL;

		Node_QUE *temp = first_node;
		//free(first_node);
		antrian->count--;
		return temp;
	}
}

void destroy_queue(Queue *antrian)
{
	Node_QUE *temp = dequeue(antrian);

	while (temp != NULL)
		temp = dequeue(antrian);
}
