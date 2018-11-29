#include<stdio.h>
#include<conio.h>
#include<windows.h>

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
/*
int main(){
	mainMenu();
	return 0;
}
*/

void mainMenu(){
	int pilihan;
	system("cls");
	for(int y=0; y<20; y++){
		for(int x=50; x<71; x++){
			if((x==50 || x==70) || (y==0 || y==19)){
				gotoXY(x,y);
				printf("%c",219);				
			}
		}
	}
	gotoXY(55,0);
	printf(" MAIN MENU ");
	
	pilihan=tulisan(1,50,20);
	
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

void gambar(char str[12]){
	for(int y=0; y<30; y++){
		for(int x=0; x<120; x++){
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
	int pilihan;
	
	gambar(" MENU PEGAWAI ");
	
	pilihan = tulisan(2,0,30);
	system("cls");
	switch(pilihan){
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: 
				mainMenu();
				break;
		default :
					system("cls");
					printf("DATA TIDAK ADA");
					getch();
					menuPegawai();
					break;
	}
}

void menuAntrian(){
	int pilihan;
	
	gambar(" MENU ANTRIAN ");
	
	pilihan = tulisan(3,0,30);
	system("cls");
	switch(pilihan){
		case 1: break;
		case 2: break;
		case 3: break;
		case 4:
				mainMenu();
				break;
		default :
					system("cls");
					printf("DATA TIDAK ADA");
					getch();
					menuAntrian();
					break;
	}
}

void menuWaiting(){
	int pilihan;
	
	gambar(" WAITING LIST ");
	
	pilihan = tulisan(4,0,30);
	system("cls");
	switch(pilihan){
		case 1: break;
		case 2: break;
		case 3: break;
		case 4:
				mainMenu();
				break;
		default :
					system("cls");
					printf("DATA TIDAK ADA");
					getch();
					menuWaiting();
					break;
	}
}

int tulisan(int menu,int x,int y){
	int pilihan;
	switch(menu){
		case 1://========== iki kanggo main menu ================
				gotoXY(x+2,3);
				printf("1.Menu Pegawai");
				gotoXY(x+2,5);
				printf("2.Antrian");
				gotoXY(x+2,7);
				printf("3.Waiting List");
				gotoXY(x+2,9);
				printf("4.EXIT");
				break;
		case 2://=========== iki kanggo Menu Pegawai ============
				gotoXY(x+2,3);
				printf("1.Edit");
				gotoXY(x+2,5);
				printf("2.Hapus");
				gotoXY(x+2,7);
				printf("3.Next");
				gotoXY(x+2,9);
				printf("4.Prev");
				gotoXY(x+2,11);
				printf("5.Back To Menu");
				break;
		case 3://=========== iki kanggo antrian ===============
				gotoXY(x+2,3);
				printf("1.Tambah Antrian");
				gotoXY(x+2,5);
				printf("2.Pop");
				gotoXY(x+2,7);
				printf("3.Edit");
				gotoXY(x+2,9);
				printf("4.Back To Menu");
				break;
		case 4://============iki kanggo waiting ===============
				gotoXY(x+2,3);
				printf("1.Tambah Antrian");
				gotoXY(x+2,5);
				printf("2.Selesai dilaksanakan");
				gotoXY(x+2,7);
				printf("3.Edit");
				gotoXY(x+2,9);
				printf("4.Back To Menu");
				break;
	}
	gotoXY(x,y+2);
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
