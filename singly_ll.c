#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 Node_SINGLY* create_node(){
	Node_SINGLY *new_node = (Node_SINGLY*)malloc(sizeof(Node_SINGLY));
	return new_node;
}
 void Insert(Node_SINGLY** head, Node_SINGLY* now, Node_SINGLY* new_node){
	if(now == NULL){
		new_node->right=*head;
		*head=new_node;
	}
	else{
		new_node->right=now->right;
		now->right=new_node;	
	}
}
 void Delete(Node_SINGLY** head,Node_SINGLY* pre, Node_SINGLY* now){
	if(pre==NULL)
		*head=now->right;
	else
		pre->right=now->right;
	free(now);
}
 void tambah_data(Node_SINGLY **head){
	Node_SINGLY* new_node = create_node();
	Node_SINGLY* temp=*head;
	
	printf("nama : ");scanf("%s",&(new_node->nama));
	printf("nip : ");scanf("%s",&(new_node->nip));
	printf("usia : ");scanf("%d",&(new_node->usia));
	
	if(temp != NULL)
		while(temp->right != NULL)
			temp=temp->right;
	
	Insert(head,temp,new_node);
}
 void cetak(Node_SINGLY* head,int next){
	Node_SINGLY* temp=head;
	int a,x=34,y=0;
	
	if(temp != NULL){
		for(a=next;a>1;a--)
			temp=temp->right;
		while(temp != NULL && a <= 5){
			gotoXY(x,y=y+2);
			printf("nama : %s\n",temp->nama);
			gotoXY(x,++y);
			printf("nip : %s\n",temp->nip);
			gotoXY(x,++y);
			printf("usia : %d\n",temp->usia);
			temp=temp->right;
			a++;
		}
	}
	else{
		gotoXY(x,y=y+2);
		printf("DATA KOSONG");	
	}
}
 void edit(Node_SINGLY** head){
	char nip[sizeof((*head)->nip)];
	Node_SINGLY* temp=*head;
	
	printf("input nip data yang ingin di-edit : ");scanf("%s",&nip);
 	while(temp != NULL && strcmp(temp->nip,nip)){
		temp=temp->right;
	}
	
	printf("nama : ");scanf("%s",&(temp->nama));
	printf("nip : ");scanf("%s",&(temp->nip));
	printf("usia : ");scanf("%d",&(temp->usia));
	
}
 void hapus(Node_SINGLY** head){
	char nip[sizeof((*head)->nip)];
	Node_SINGLY* temp=*head,*pre=NULL;
	
	printf("input nip data yang ingin di-hapus : ");scanf("%s",&nip);
	
	while(temp != NULL && strcmp(temp->nip,nip)){
		pre=temp;
		temp=temp->right;
	}
	
	Delete(head,pre,temp);
}
