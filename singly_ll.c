#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//=========================STRUCT DEFINITION======================
struct node 
{
	struct node *next;
	char nip[30], nama[100], pendidikan[30], jabatan[30];
};

//========================FUNCTION DEFINITION=====================

void deleteNode(node **head, node *pPre, node *pCur);
void deleteList(node *head);
void tambahData(node **head);	
void updateData(node **head);	
void hapusData(node **head);	
void showData(node *head);		

//==========================MAIN==================================

int main()
{
	node *head=NULL;
	char pilih;

	do
	{
		system("cls");
     
    	printf("=======MENU DAFTAR PEGAWAI KUA=======\n");
    	printf("1. TAMBAH DATA PEGAWAI\n");
    	printf("2. UBAH DATA PEGAWAI\n");
    	printf("3. HAPUS DATA PEGAWAI\n");
    	printf("4. LIHAT DAFTAR PEGAWAI\n");
    	printf("\nMASUKKAN PILIHAN (tekan q untuk keluar) : ");
     
    	scanf("%c", &pilih);
    	fflush(stdin);
     
    	if (pilih == '1')
    		tambahData(&head);
		
    	else if (pilih == '2')
    		updateData(&head);
		
    	else if (pilih == '3')
    		hapusData(&head);
		
    	else if (pilih == '4')
		{
    	 	showData(head);
        	getch();
    	} 
	} 
	while (pilih != 'q');
	deleteList(head);
}

//===========================DELETE NODE==========================

void deleteNode(node **head, node *pPre, node *pCur)
{
	if (pPre == NULL)
		*head = pCur -> next;
	
	else
	{
		pPre -> next = pCur -> next;
	}
	free(pCur);
}

//============================DELETE LIST=========================

void deleteList(node *head)
{
	node *pTemp;
	
	while(head != NULL)
	{
		pTemp = head;
		head = head->next;
		free(pTemp);
	}
}

//============================TAMBAH DATA=========================

void tambahData(node **head)
{
	node *pegawai;
	char nip[30], nama[100], pendidikan[30], jabatan[30];
	
	system("cls");
	
	fflush(stdin);
	printf("Masukkan NIP\t\t: ");
	scanf("%s",&nip);
	
	fflush(stdin);
	printf("Masukkan Nama\t\t: ");
	scanf("%[^\n]s",&nama);
	
	fflush(stdin);
	printf("Masukkan Pendidikan\t: ");
	scanf("%s",&pendidikan);
	
	fflush(stdin);
	printf("Masukkan Jabatan\t: ");
	scanf("%[^\n]s",&jabatan);
	
	pegawai = (node *)malloc(sizeof(node));
	
	strcpy(pegawai->nip,nip);
	strcpy(pegawai->nama,nama);
	strcpy(pegawai->pendidikan,pendidikan);
	strcpy(pegawai->jabatan,jabatan);
	pegawai->next = NULL;
	
	if(*head==NULL)
		*head = pegawai;
		
	else
	{
		pegawai->next = *head;	
		*head = pegawai;
	}
	printf("\n");	
}

//===========================UPDATE DATA==========================

void updateData(node **head)
{
	node *pNew=*head;
	char nip[30], nip2[30], nama[100], pendidikan[30], jabatan[30];	
	system("cls");
	
	showData(*head);
  	printf("Data yang akan diubah \nNIP\t\t: ");
  	fflush(stdin);
  	scanf("%s",&nip2);
  	
  	
	while(pNew!=NULL && strcmp(pNew->nip,nip2))
		pNew = pNew->next;
	
  	if(pNew != NULL)
	{
	  	printf("Data yang akan diubah \nNIP\t\t\t: ");
	  	fflush(stdin);
	  	scanf("%s",&nip);
	
	  	printf("Masukkan Nama\t\t: ");
	  	fflush(stdin);
	  	scanf("%[^\n]s",&nama);
	  	
		printf("Masukkan Pendidikan\t: ");
		fflush(stdin);
		scanf("%s",&pendidikan);
		
		printf("Masukkan Jabatan\t: ");
		fflush(stdin);
		scanf("%[^\n]s",&jabatan);
	
		strcpy(pNew->nip,nip);
		strcpy(pNew->nama,nama);
		strcpy(pNew->pendidikan,pendidikan);
		strcpy(pNew->jabatan,jabatan);
	}
	else
	{
		printf("\nData tidak ditemukan");
		getch();
	}
}

//============================DELETE DATA=========================

void hapusData(node **head)
{
	char nip2[30];
	node *pCur, *pPre;

	system("cls");
	showData(*head);
	printf("\nData yang akan dihapus \nNIP\t\t: ");
	fflush(stdin);
	scanf("%s", &nip2);

	pPre = NULL;
	pCur = *head;
	//cari target value sampai ditemukan atau sampai pada akhir list
	while (pCur != NULL && strcmp(pCur->nip,nip2))
	{
		pPre = pCur;
		pCur = pCur -> next;
	}

	if (pCur == NULL)
	{
		printf("\nData tidak ditemukan");
    	getch();
	}
	else
		deleteNode(head, pPre, pCur);
	
}

//============================SHOW DATA===========================

void showData(node *head)
{
	node *pWalker=head;
	int dataKe=1;
	
    system("cls");
    
    if(pWalker != NULL)
    {
    	while(pWalker != NULL)
		{
			printf("===========================================");
			printf("\nDATA %i\n", dataKe);
			printf("===========================================");
    		printf("\nNIP\t\t: %s\n",pWalker->nip);
    		printf("Nama\t\t: %s\n",pWalker->nama);
    		printf("Pendidikan\t: %s\n",pWalker->pendidikan);
    		printf("Jabatan\t\t: %s\n\n",pWalker->jabatan);
    		dataKe++;
    		pWalker=pWalker->next;
		}
	}
	else
		printf("Data Kosong");
}
