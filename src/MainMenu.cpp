#include"header.h"
#include <conio.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y);
int tulisan(int menu,int x,int y); // tulisan() = menampilkan tulisan pada menu (kode menu, koordinat x awal, koordinat y akhir)
void mainMenu();
void menuPegawai(int &jmlhPegawai);
void menuAntrian(int &jmlhAntrian, int &jmlhWaiting);
void menuWaiting(int &jmlhWaiting);
void gambar(const char *str);

//kurang antrian dan waiting list
//menune menuAntrian

static Node_SINGLY *head_sing = NULL;
static Queue antrian = createQueue();
static Node_AVL *root_avl = NULL;

int main() {
	int y=0;
	system("cls");

	mainMenu();

	destroy_tree(&root_avl);
	destroy_queue(&antrian);
	destroy_list(&head_sing);

	return 0;
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
				menuPegawai(jmlhPegawai);
				break;
			case 2:
				menuAntrian(jmlhAntrian, jmlhWaiting);
				break;
			case 3:
				menuWaiting(jmlhWaiting);
				break;
			case 4:
				break;
			default:
				printf("PILIHAN TIDAK ADA");
				getch();
		}
	} while(pilihan != 4);
}

void gambar(const char *str) {
	system("cls");
	for(int y=0; y<30; y++) {
		for(int x=0; x<120; x++) {
			if ((x == 0 || x == 119 || x == 30 || x == 31) || (y == 0 || y == 29)) {
				gotoXY(x,y);
				printf("%c", 219);
			}
		}
	}
	gotoXY(57, 0);
	printf("%s", str);
}

void menuPegawai(int &jmlhPegawai) {
	int pilihan, a = 1;
	do {
		gambar("MENU PEGAWAI");
		cetak(head_sing, a);

		pilihan = tulisan(2, 0, 3);

		system("cls");
		switch(pilihan) {
			case 1:
				if (tambah_data(&head_sing))
					jmlhPegawai++;
				getch();
				break;
			case 2:
				edit(&head_sing);
				getch();
				break;
			case 3:
				if (a+5 <= jmlhPegawai)
					a=a+5;
				break;
			case 4:
				if (a-5 > 0)
					a=a-5;
				break;
			case 5:
				if (hapus(&head_sing))
					jmlhPegawai--;
				getch();
				break;
		}
	} while (pilihan != 6);
}

void menuAntrian(int &jmlhAntrian, int &jmlhWaiting) {
	int pilihan, batas=1;
	Node_SINGLY *pegawai = NULL;
	Node_QUE *hasilProses = NULL;

	do {
		gambar(" MENU ANTRIAN ");
		display(antrian,batas);

		pilihan = tulisan(3, 0, 3);

		system("cls");
		switch (pilihan) {
			case 1:
				enqueue(&antrian);
				getch();
				break;
			case 2:
				pegawai = gunakan_pegawai(&head_sing);

				if (pegawai) {	// Cek apabila pegawai tidak sibuk
					hasilProses = dequeue(&antrian);

					if (hasilProses) {
						Data_FIX berkas;

						fflush(stdin);
						printf("Nama penghulu\t\t: %s\n", pegawai->nama);
						strcpy(berkas.nama_penghulu, pegawai->nama);
						printf("NIP penghulu\t\t: %s\n", pegawai->nip);
						strcpy(berkas.nip_penghulu, pegawai->nip);
						printf("Nama calon suami\t: %s\n", hasilProses->casa);
						strcpy(berkas.casa, hasilProses->casa);
						printf("NIK calon suami\t\t: %s\n", hasilProses->nik);
						strcpy(berkas.nik_casa, hasilProses->nik);
						printf("Nama calon istri\t: ");
						scanf("%[^\n]%*c", &(berkas.casi));
						printf("NIK calon istri\t\t: ");
						scanf("%s",&(berkas.nik_casi));
						printf("Nomor telp\t\t: ");	// Yang bisa dihubungi
						scanf("%u", &(berkas.no_telp));
						fflush(stdin);
						printf("Alamat\t\t\t: ");		// Lokasi pernikahan maksute?
						scanf("%[^\n]%*c",&(berkas.alamat));
						printf("Tanggal pernikahan\t: ");
						scanf("%s", &(berkas.tgl_nikah));
						
						printf("\nData di atas akan dimasukan ke dalam waiting list.");
						
						jmlhAntrian--;
						jmlhWaiting++;
						
						waiting_list(&root_avl, berkas);
						free(hasilProses);
					}
					else {
						printf("Antrian kosong!");
					}
				}
				else {
					printf("Pegawai sedang sibuk semua.");
				}
				getch();
				break;
			case 3:
				if (batas+3 <= jmlhAntrian)
					batas += 3;
				break;
			case 4:
				if (batas-3 > 0)
					batas -= 3;
				break;
			case 5:
				break;
			default:
				printf("DATA TIDAK ADA");
				getch();
				//menuAntrian();
				break;
		}
	} while(pilihan != 5);
}

void menuWaiting(int &jmlhWaiting) {
	int pilihan, batasBawah=1, batasAtas=3, y;
	char tanggal[11];
	do {
		y = 0;
		batasAtas = batasBawah + 3;
		gambar(" WAITING LIST ");
		inorder(root_avl, batasBawah, y, batasAtas);
		pilihan = tulisan(4, 0, 3);
		switch (pilihan) {
			case 1:
				done(&root_avl, &head_sing);
				getch();
				break;
			case 2:
				//	mainMenu();
				break;
			case 3:
				system("cls");
				printf("tanggal yang ingin di batalkan (format : dd-mm-yyyy) : ");
				scanf("%s",tanggal);
				cancel(&root_avl, tanggal, &head_sing);
				getch();
				break;
			case 4:
				if (batasBawah+7 <= jmlhWaiting)
					batasBawah+=4;
				break;
			case 5:
				if (batasBawah > 0 )
					batasBawah-=4;
				break;
			default :
				system("cls");
				printf("DATA TIDAK ADA");
				getch();
				break;
		}
		system("cls");
	} while (pilihan != 2);
}

int tulisan(int menu, int x, int y) {
	int pilihan;
	switch (menu) {
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
	gotoXY(x+2, y+2);
	printf("input pilihan : ");
	scanf("%d", &pilihan);
	return pilihan;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed
}
