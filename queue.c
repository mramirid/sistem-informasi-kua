#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	struct node *next, *prev;
	int nomor_antrian;
	char casa[100], casi[100], alamat[100], tgl_nikah[100], lengkapdata[10];	
};

//================================================

struct queue
{
	int count;
	node *front;
	node *rear;
};

int main(){

printf("Hello world");

}
