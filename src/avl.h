#ifndef _AVL_
#define _AVL_

struct Node_AVL
{
	char nama_penghulu[30];
	unsigned long long nip_penghulu;
	char casa[30], casi[30];
	unsigned long long nik_casa, nik_casi, no_telp;
	char alamat[30], tgl_nikah[11];
    int height;
    struct Node_AVL *left, *right;
};
typedef struct Node_AVL Node_AVL;

// TAK PAKAI INI DARIPADA PASSING BANYAK PARAMETER
struct Data_FIX
{
	char nama_penghulu[30];
	unsigned long long nip_penghulu;
	char casa[30], casi[30];
	unsigned long long nik_casa, nik_casi, no_telp;
	char alamat[30], tgl_nikah[11];
};
typedef struct Data_FIX Data_FIX;

#endif // _AVL_