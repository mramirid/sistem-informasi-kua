#include "header.h"
#include <string.h>

Node_SINGLY* create_node() {
	Node_SINGLY *new_node = (Node_SINGLY*)malloc(sizeof(Node_SINGLY));
	return new_node;
}

void Insert(Node_SINGLY **head, Node_SINGLY *now, Node_SINGLY *new_node) {
	if (now == NULL) {
		new_node->right=*head;
		*head=new_node;
	}
	else {
		new_node->right = now->right;
		now->right = new_node;
	}
}

void Delete(Node_SINGLY **head, Node_SINGLY *pre, Node_SINGLY *now) {
	if (pre == NULL)
		*head = now->right;
	else
		pre->right = now->right;

	free(now);
}

void tambah_data(Node_SINGLY **head) {
	Node_SINGLY* new_node = create_node();
	Node_SINGLY* temp = *head;

	fflush(stdin);
	printf("\nNama\t: ");
	scanf("%[^\n]%*c", &(new_node->nama));
	printf("NIP\t: ");
	scanf("%s", &(new_node->nip));
	printf("Usia\t: ");
	scanf("%d", &(new_node->usia));

	if (temp != NULL)
		while (temp->right != NULL)
			temp=temp->right;

	Insert(head, temp, new_node);
	printf("\nData berhasil dimasukan.");
}

void cetak(Node_SINGLY *head, int next) {
	Node_SINGLY* temp = head;
	int a, x = 34, y = 0;

	if (temp != NULL) {
		for (a=next; a>1; a--)
			temp = temp->right;
		while (temp != NULL && a <= 5) {
			gotoXY(x, y += 2);
			printf("Nama\t: %s\n", temp->nama);
			gotoXY(x, ++y);
			printf("NIP\t: %s\n", temp->nip);
			gotoXY(x, ++y);
			printf("Usia\t: %d\n", temp->usia);
			temp = temp->right;
			a++;
		}
	}
	else {
		gotoXY(x, y += 2);
		printf("DATA KOSONG");
	}
}

void edit(Node_SINGLY **head) {
	char nip[20];
	Node_SINGLY *temp = *head;

	printf("Input NIP data yang ingin sunting: ");
	scanf("%s", &nip);
 	while (temp != NULL && strcmp(temp->nip, nip))
		temp = temp->right;

	if (temp == NULL)
		printf("\nData tidak ditemukan!");
	else
	{
		printf("Nama\t: ");
		scanf("%s", &(temp->nama));
		printf("NIP\t: ");
		scanf("%s", &(temp->nip));
		printf("Usia\t: ");
		scanf("%d", &(temp->usia));
		printf("\nData berhasil disunting.");
	}
}

void hapus(Node_SINGLY **head) {
	char nip[20];
	Node_SINGLY* temp = *head, *pre = NULL;

	printf("Input NIP data yang ingin dihapus: ");
	scanf("%s", &nip);

	while (temp != NULL && strcmp(temp->nip, nip)) {
		pre = temp;
		temp = temp->right;
	}

	if (temp == NULL)
		printf("\nData tidak ditemukan!");
	else
	{
		Delete(head, pre, temp);
		printf("\nData berhasil dihapus.");
	}
}
