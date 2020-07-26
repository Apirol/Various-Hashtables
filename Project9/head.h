#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

const int  N = 2000;
extern int num;
using namespace std;

struct table
{
	char code[9];
	char name[255];
	int numb;
	int price;
};

struct itemField
{
	char name[255];
	int numb;
	int price;
};

void hashTable_add(table *t, char *code, char *name, int numb);
int hash_f(table *t, int hash, int sym);
void inclusionSort(table *t);
void bubbleSort(table *t); 
void shellSort(table *t);
void priceList(map <string, int> &tablePrice);
void inputPrice(table *t, map <string, int> tablePrice);
void sortTa(map <string, itemField> &sortTable, table *t,int &num);