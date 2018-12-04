#include"header.h"
#include <conio.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y);
int tulisan(int menu,int x,int y);//tulisan() = menampilkan tulisan pada menu (kode menu, koordinat x awal, koordinat y akhir)
void mainMenu();
void menuPegawai();
void menuAntrian();
void menuWaiting();
void gambar(char str[14]);

//kurang antrian dan waiting list
//menune menuAntrian

static Node_SINGLY* head_sing=NULL;
static Queue antrian = createQueue();
static Node_AVL *root = NULL;

int main(){
	int y=0;
	system("cls");
	
	mainMenu();

	return 0;
}

void mainMenu(){
	int pilihan,x,y;
	system("cls");
	for(y=0; y<20; y++){
		for(x=48; x<73; x++){
			if((x==48 || x==72) || (y==0 || y==19)){
				gotoXY(x,y);
				printf("%c",219);
			}
		}
	}
	gotoXY(55,0);
	printf(" MAIN MENU ");

	pilihan=tulisan(1,50,2);

	system("cls");
	switch(pilihan){
		case 1:menuPegawai();break;
		case 2:menuAntrian();break;
		case 3:menuWaiting();break;
		case 4:exit(0);break;
		default :
					system("cls");
					printf("DATA TIDAK ADA");
					getch();
					mainMenu();
					break;
	}
}

void gambar(const char str[12]){
	int x,y;
	for(y=0; y<30; y++){
		for(x=0; x<120; x++){
			if((x==0 || x==119 || x==30 || x==31) || (y==0 || y==29)){
				gotoXY(x,y);
				printf("%c",219);
			}
		}
	}
	gotoXY(57,0);
	printf("%s",str);
}

void menuPegawai(){
	int pilihan,a=1;
	do{
		system("cls");
		gambar("MENU PEGAWAI");
		cetak(head_sing,a);

		pilihan = tulisan(2,0,3);
		system("cls");

		switch(pilihan){
			case 1:
				tambah_data(&head_sing);
				break;
			case 2:
				edit(&head_sing);
				break;
			case 3:
				a=a+5;
				break;
			case 4:
				a=a-5;
				break;
			case 5:
				hapus(&head_sing);
				break;
			case 6:
				mainMenu();
				break;
		}
	}while(pilihan != 6);
}

void menuAntrian(){
	int pilihan, batas=1;
	Node_QUE *hasilProses;
	do{

		gambar(" MENU ANTRIAN ");
		display(antrian,batas);

		pilihan = tulisan(3,0,3);

		system("cls");
		switch(pilihan){
			case 1:
					enqueue(&antrian);
					break;
			case 2:
					hasilProses=dequeue(&antrian);
					break;
			case 3:
					batas+=3;
					break;
			case 4:
					batas-=3;
					break;
			case 5:
					mainMenu();
					break;
			default :
				system("cls");
				printf("DATA TIDAK ADA");
				getch();
				menuAntrian();
				break;
		}
		system("cls");
	}while(pilihan != 6);
}

void menuWaiting(){
	int pilihan,batasBawah=1,batasAtas=3,y=0;
	system("cls");
	do{
		y=0;
		batasAtas=batasBawah+3;
		gambar(" WAITING LIST ");
		inorder(root,batasBawah,y,batasAtas);
		pilihan = tulisan(4,0,3);
		switch(pilihan){
			case 1: break;
			case 2:
					mainMenu();
					break;
			case 3:
					root = insert(root,20181112,"aaa","bbb","cccc","20181112");
					root = insert(root,20181111,"aaa","bbb","cccc","20181111");
					root = insert(root,20181108,"aaa","bbb","cccc","20181108");
					root = insert(root,20181109,"aaa","bbb","cccc","20181109");
					root = insert(root,20181116,"aaa","bbb","cccc","20181116");
					root = insert(root,20181129,"aaa","bbb","cccc","20181129");
					break;
			case 4: batasBawah+=4;
					break;
			case 5: batasBawah-=4;
					break;
			default :
					system("cls");
					printf("DATA TIDAK ADA");
					getch();
					menuWaiting();
					break;
		}
		system("cls");
	}while(pilihan != 2);
}

int tulisan(int menu,int x,int y){
	int pilihan;
	switch(menu){
		case 1://========== iki kanggo main menu ================
				gotoXY(x+2,y);
				printf("1.Menu Pegawai");
				gotoXY(x+2,y+=2);
				printf("2.Antrian");
				gotoXY(x+2,y+=2);
				printf("3.Waiting List");
				gotoXY(x+2,y+=2);
				printf("4.EXIT");
				break;
		case 2://=========== iki kanggo Menu Pegawai ============
				gotoXY(x+2,y);
				printf("1.tambah");
				gotoXY(x+2,y+=2);
				printf("2.edit");
				gotoXY(x+2,y+=2);
				printf("3.Next");
				gotoXY(x+2,y+=2);
				printf("4.Prev");
				gotoXY(x+2,y+=2);
				printf("5.hapus");
				gotoXY(x+2,y+=2);
				printf("6.Back To Menu");
				break;
		case 3://=========== iki kanggo antrian ===============
				gotoXY(x+2,y);
				printf("1.Tambah Antrian");
				gotoXY(x+2,y+=2);
				printf("2.Proses Antrian");
				gotoXY(x+2,y+=2);
				printf("3.Next");
				gotoXY(x+2,y+=2);
				printf("4.Prev");
				gotoXY(x+2,y+=2);
				printf("5.Back To Menu");
				break;
		case 4://============iki kanggo waiting ===============
				gotoXY(x+2,y);
				printf("1.Selesai dilaksanakan /");
				gotoXY(x+4,y+=1);
				printf("Dibatalkan");
				gotoXY(x+2,y+=2);
				printf("2.Back To Menu");
				gotoXY(x+2,y+=2);
				printf("3.Tambah(cumn buat nyoba)");
				gotoXY(x+2,y+=2);
				printf("4.Next");
				gotoXY(x+2,y+=2);
				printf("5.Prev");
				break;
	}
	gotoXY(x+2,y+2);
	printf("input pilihan : ");
	scanf("%d",&pilihan);
	return pilihan;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}
