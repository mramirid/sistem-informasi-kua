#ifndef _SINGLY_LL_
#define _SINGLY_LL_

struct Node_SINGLY
{
	char nama[30];
	unsigned long long nip;
	int terpakai, usia;
	struct Node_SINGLY *right;
};
typedef struct Node_SINGLY Node_SINGLY;

#endif  // _SINGLY_LL_