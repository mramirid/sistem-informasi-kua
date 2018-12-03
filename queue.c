#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//==============================
struct node
{
	struct node *next, *prev;
	int nomor_antrian;
	char casa[100], casi[100], alamat[100], tgl_nikah[100], lengkapdata[10];
};
typedef struct node Node;

struct queue
{
	int count;
	node *front;
	node *rear;
};
typedef struct queue Queue;

Queue createQueue();
bool isEmpty(Queue antrian);
void enqueue(Queue *antrian);
void display(Queue antrian);
void update(Queue antrian);
int dequeue(Queue *antrian);

/*==============================*/
int main()
{
	Queue antrian = createQueue();
	int pilihan;
	do
	{
		system("CLS");
		printf("===========================\n");
		printf("1.|  Input Antrian KUA    |\n");
		printf("2.|  Show Antrian KUA     |\n");
		printf("3.|  Update Antrian KUA   |\n");
		printf("4.|  Delete Antrian KUA   |\n");
		printf("5.|  EXIT                 |\n");
		printf("===========================\n");
		printf("Masukan pilihan: ");
		scanf("%d", &pilihan);
		fflush(stdin);

		system("CLS");
		switch (pilihan)
		{
		case 1 :
				enqueue(&antrian);
				break;
		case 2 :
				display(antrian);
				break;
		case 3 : 
				update(antrian);
				break;
		case 4 :
				dequeue(&antrian);
				break;
		case 5 : 
				exit(1);
		}
		getch();
	}   
		while (pilihan != 'q');
}
		
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
		char casa[100];
		char casi[100];
		char alamat[100];
		char tgl_nikah[100];
		char lengkapdata[10];

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
		
		Node *new_node = (Node *)malloc(sizeof(Node));
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

void display(Queue antrian)
{
	int num;
	Node *current = antrian.front;
	while (current != NULL){
		for(num = 1; current != NULL; num ++)
		{
		printf("=== Antrian Ke - %d ===\n", num);
		printf("Nomor Antrian : %d\n", current->nomor_antrian);
		fflush(stdin);
		printf("Casa          : %s\n", current->casa);
		fflush(stdin);
		printf("Casi          : %s\n", current->casi);
		fflush(stdin);
		printf("Alamat        : %s\n", current->alamat);
		fflush(stdin);
		printf("Tanggal Nikah : %s\n", current->tgl_nikah);
		fflush(stdin);
		printf("Data Lengkap  : %s\n", current->lengkapdata);
		fflush(stdin);
		printf("\n");
		current = current->next;
		}
	}
	printf("NULL");
}

void update(Queue antrian)
{
	long long int pos;
	node *pCur, *pPre, *front=antrian.front;
	long long int nomor_antrian;
	char casa[100];
	char casi[100];
	char alamat[100];
	char tgl_nikah[100];
	char lengkapdata[100];	
	system("cls");
	
	display(antrian);
	printf("\nCari data yang akan diupdate ( 'Nomor Antrian' ): ");
	fflush(stdin); 
	scanf("%lli", &pos);
	pPre = NULL;
	pCur = front;
	while (pCur != NULL && pCur -> nomor_antrian != pos) {
		pPre = pCur;
		pCur = pCur -> next;
	}
	if (pCur == NULL){
		printf("\nNomor Antrian tidak ditemukan"); getch();
	}
	else{
		system("cls");
		printf("===Data yang diUbah===\n");
		printf("Nomor Antrian\t: "); 
		scanf("%lli", &nomor_antrian);
		fflush(stdin);
		printf("Casa\t: "); 
		scanf("%[^\n]%*c", &casa);
		fflush(stdin);
		printf("Casi\t: "); 
		scanf("%[^\n]%*c", &casi);
		fflush(stdin);
		printf("Alamat\t: "); 
		scanf("%[^\n]%*c", &alamat);
		fflush(stdin);
		printf("Tanggal Nikah\t: "); 
		scanf("%[^\n]%*c", &tgl_nikah);
		printf("Lengkap Data\t:");
		scanf("%[^\n]%*c", &lengkapdata);			
		pCur->nomor_antrian = nomor_antrian;
		strcpy(pCur->casa, casa);
		strcpy(pCur->casi, casi);
		strcpy(pCur->alamat, alamat);
		strcpy(pCur->tgl_nikah, tgl_nikah);
		strcpy(pCur->lengkapdata, lengkapdata);
		
		pCur->nomor_antrian = nomor_antrian;
	}
}
	
int dequeue(Queue *antrian)
{
	node *pCur, *next;
	
	if (isEmpty(*antrian)){
		printf("Data masih kosong, silahkan diisi terlebih dahulu!");
		return 0;
	}
	else{
		printf("Data Antrian Awal Telah Dihapus!!");
		Node *first_node = antrian->front;
		antrian->front = first_node->next;

		if (antrian->count == 1)
			antrian->rear = NULL;
		free(first_node);
		antrian->count--;
		return 1;
	}
}
