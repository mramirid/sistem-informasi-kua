#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "singly_ll.h"
#include "queue.h"
#include "avl.h"

// Singly Linked-list
int tambah_data(Node_SINGLY **head);
void cetak(Node_SINGLY *head, int next); // Variabel next, awal data mana yang ditampilkan.
void edit(Node_SINGLY **head);
int hapus(Node_SINGLY **head);
void destroy_list(Node_SINGLY **head);
Node_SINGLY* gunakan_pegawai(Node_SINGLY **head);

// Queue
Queue createQueue();
void enqueue(Queue *antrian);
Node_QUE* dequeue(Queue *antrian);
void display(Queue antrian, int batas);
void destroy_queue(Queue *antrian);

// AVL Tree
Node_AVL* insert(Node_AVL *node, Data_FIX berkas);
Node_AVL* min_value_node(Node_AVL *node);
void destroy_tree(Node_AVL **node);
int inorder(Node_AVL *node, int batasBawah, int *y, int batasAtas);
void waiting_list(Node_AVL **node, Data_FIX berkas);
int cancel(Node_AVL **node, unsigned long long nik_casa, Node_SINGLY **head, int flag);
int search(Node_AVL *node, const char tanggal_nikah[11], int flag);

Node_SINGLY *head_sing;
Queue antrian;
Node_AVL *root_avl;

void gotoXY(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row

	// Sets position for next thing to be printed
	SetConsoleCursorPosition(console, CursorPosition);
}

void gambar(const char *str) {
	system("cls");
	for (int y=0; y<30; y++) {
		for (int x=0; x<120; x++) {
			if ((x == 0 || x == 119 || x == 30 || x == 31) || (y == 0 || y == 29)) {
				gotoXY(x,y);
				printf("%c", 219);
			}
		}
	}
	gotoXY(57, 0);
	printf("%s", str);
}

// tulisan() = menampilkan tulisan pada menu (kode menu, koordinat x awal, koordinat y akhir)
int tulisan(int menu, int x, int y) {
	int pilihan;
	switch (menu) {
		case 1:	//========== iki kanggo main menu ================
			gotoXY(x + 2, y);
			printf("1.Menu Pegawai");
			gotoXY(x + 2, y += 2);
			printf("2.Antrian");
			gotoXY(x + 2, y += 2);
			printf("3.Waiting List");
			gotoXY(x + 2, y += 2);
			printf("4.EXIT");
			break;
		case 2:	//=========== iki kanggo Menu Pegawai ============
			gotoXY(x + 2, y);
			printf("1. Tambah data");
			gotoXY(x + 2, y += 2);
			printf("2. Edit data");
			gotoXY(x + 2, y += 2);
			printf("3. Hapus data");
			gotoXY(x + 2, y += 2);
			printf("4. Next");
			gotoXY(x + 2, y += 2);
			printf("5. Prev");
			gotoXY(x + 2, y += 2);
			printf("6. Back to menu");
			break;
		case 3:	//=========== iki kanggo antrian ===============
			gotoXY(x + 2, y);
			printf("1. Tambah Antrian");
			gotoXY(x + 2, y += 2);
			printf("2. Proses Antrian");
			gotoXY(x + 2, y += 2);
			printf("3. Next");
			gotoXY(x + 2, y += 2);
			printf("4. Prev");
			gotoXY(x + 2, y += 2);
			printf("5. Back to menu");
			break;
		case 4:	//============iki kanggo waiting ===============
			gotoXY(x + 2, y);
			printf("1. Cari data");
			gotoXY(x + 2, y += 2);
			printf("2. Dibatalkan/Telah selesai");
			gotoXY(x + 2, y += 2);
			printf("3. Next");
			gotoXY(x + 2, y += 2);
			printf("4. Prev");
			gotoXY(x + 2, y += 2);
			printf("5. Back to menu");
			break;
	}
	gotoXY(x + 2, y + 2);
	printf("input pilihan : ");
	scanf("%d", &pilihan);
	return pilihan;
}

void menuPegawai(int *jmlhPegawai) {
	int pilihan, a = 1;
	do {
		gambar("MENU PEGAWAI");
		cetak(head_sing, a);

		pilihan = tulisan(2, 0, 3);

		system("cls");
		switch(pilihan) {
			case 1:
				if (tambah_data(&head_sing))
					(*jmlhPegawai)++;
				getch();
				break;
			case 2:
				edit(&head_sing);
				getch();
				break;
			case 3:
				if (hapus(&head_sing))
					(*jmlhPegawai)--;
				getch();
				break;
			case 4:
				if ((a + 5) <= *jmlhPegawai)
					a += 5;
				break;
			case 5:
				if ((a - 5) > 0)
					a -= 5;
				break;
			case 6:
				break;
			default:
				printf("Pilihan Tidak Ada");
				getch();
				break;
		}
	} while (pilihan != 6);
}

void menuAntrian(int *jmlhWaiting) {
	int pilihan, batas = 1;
	Node_SINGLY *pegawai = NULL;
	Node_QUE *hasilProses = NULL;

	do {
		gambar(" MENU ANTRIAN ");
		display(antrian, batas);

		pilihan = tulisan(3, 0, 3);

		system("cls");
		switch (pilihan) {
			case 1:
				enqueue(&antrian);
				getch();
				break;
			case 2:
				if (antrian.count > 0)
					pegawai = gunakan_pegawai(&head_sing);

				if (pegawai) {	// Cek apabila pegawai tidak sibuk
					hasilProses = dequeue(&antrian);

					if (hasilProses) {
						Data_FIX berkas;

						fflush(stdin);
						printf("Nama penghulu\t\t: %s\n", pegawai->nama);
						strcpy(berkas.nama_penghulu, pegawai->nama);
						printf("NIP penghulu\t\t: %llu\n", pegawai->nip);
						berkas.nip_penghulu = pegawai->nip;
						printf("Nama calon suami\t: %s\n", hasilProses->casa);
						strcpy(berkas.casa, hasilProses->casa);
						printf("NIK calon suami\t\t: %llu\n", hasilProses->nik_casa);
						berkas.nik_casa = hasilProses->nik_casa;
						printf("Nama calon istri\t: ");
						scanf("%[^\n]%*c", &(berkas.casi));
						printf("NIK calon istri\t\t: ");
						scanf("%llu",&(berkas.nik_casi));
						printf("Nomor telp\t\t: ");	// Yang bisa dihubungi
						scanf("%llu", &(berkas.no_telp));
						fflush(stdin);
						printf("Alamat\t\t\t: ");		// Lokasi pernikahan maksute?
						scanf("%[^\n]%*c",&(berkas.alamat));
						printf("Tanggal pernikahan\t: ");
						scanf("%s", &(berkas.tgl_nikah));
						
						printf("\nData di atas akan dimasukan ke dalam waiting list.");
						
						(*jmlhWaiting)++;
						
						waiting_list(&root_avl, berkas);
						free(hasilProses);
					}
					else
						printf("Antrian kosong!");
				}
				else
					printf("Pegawai sedang sibuk semua.");
				getch();
				break;
			case 3:
				if ((batas + 6) <= antrian.count)
					batas += 6;
				break;
			case 4:
				if ((batas - 6) > 0)
					batas -= 6;
				break;
			case 5:
				break;
			default:
				printf("MENU PILIHAN TIDAK ADA");
				getch();
				break;
		}
	} while(pilihan != 5);
}

void menuWaiting(int *jmlhWaiting) {
	int pilihan, batasBawah = 1, batasAtas = 2, y;
	unsigned long long nik_casa;
	Node_AVL *temp = NULL;
	char cari[11];
	do {
		y = 0;
		batasAtas = batasBawah + 2;

		gambar(" WAITING LIST ");
		if (root_avl == NULL) {
			gotoXY(35, y + 2);
			printf("DATA KOSONG");
		}
		else
			inorder(root_avl, batasBawah, &y, batasAtas);

		pilihan = tulisan(4, 0, 3);

		switch (pilihan) {
			case 1:
				if (root_avl != NULL) {
					system("cls");
					printf("Input Tanggal: ");
					scanf("%s", &cari);
					if (!search(root_avl, cari, 0))
						printf("\n\nData tidak ada.");
				}
				else {
					system("cls");
					printf("Waiting List masih kosong.");
				}
				getch();
				break;
			case 2:
				system("cls");
				if (root_avl != NULL) {
					printf("NIK Calon suami: ");
					scanf("%llu", &nik_casa);
					if (cancel(&root_avl, nik_casa, &head_sing, 0))
						--(*jmlhWaiting);
				}
				else
					printf("Waiting List masih kosong.");
				getch();
				break;
			case 3:
				if ((batasBawah + 3) <= *jmlhWaiting)
					batasBawah += 3;
				break;
			case 4:
				if ((batasBawah - 3) > 0 )
					batasBawah -= 3;
				break;
			case 5:
				break;
			default :
				system("cls");
				printf("PILIHAN TIDAK ADA");
				getch();
				break;
		}
		system("cls");
	} while (pilihan != 5);
}

void mainMenu() {
	int pilihan, jmlhPegawai = 0, jmlhAntrian = 0, jmlhWaiting = 0;
	do {
		system("cls");
		for( int y=0; y<20; y++) {
			for( int x=48; x<73; x++) {
				if ((x == 48 || x == 72) || (y == 0 || y == 19)) {
					gotoXY(x, y);
					printf("%c", 219);
				}
			}
		}

		gotoXY(55, 0);
		printf(" MAIN MENU ");

		pilihan = tulisan(1, 50, 2);

		system("cls");
		switch(pilihan) {
			case 1:
				menuPegawai(&jmlhPegawai);
				break;
			case 2:
				menuAntrian(&jmlhWaiting);
				break;
			case 3:
				menuWaiting(&jmlhWaiting);
				break;
			case 4:
				break;
			default:
				printf("PILIHAN TIDAK ADA");
				getch();
		}
	} while(pilihan != 4);
}

int main() {
	head_sing = NULL;
	antrian = createQueue();
	root_avl = NULL;

	mainMenu();

	destroy_list(&head_sing);
	destroy_queue(&antrian);
	destroy_tree(&root_avl);

	return 0;
}
