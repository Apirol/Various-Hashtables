#include <stdio.h>
#include <string.h>
#include "head.h"
#include <conio.h>
#include <string>
#include <map>
#include <fstream>


using namespace std;

void hashTable_add(table *t, char *code, char *name, int numb) // Хеш-таблица
{
	int flag = 0;
	for (int i = 0; i < N && !flag; i++)
		if (!strcmp(code, t[i].code))
		{
			flag++;
			t[i].numb += numb;
		}
	if (!flag)
	{
		int sym = 0;
		for (int i = 0; i < 9; i++)
			sym += code[i];
		int hash = sym % N;
		hash = hash_f(t, hash, sym);
		if (!strlen(t[hash].code))
		{
			strcpy(t[hash].code, code);
			strcpy(t[hash].name, name);
			t[hash].numb = numb;
		}
	}
}

int hash_f(table *t, int hash, int sym) // Хеш функция
{
	for (int i = 1; i < N && strlen(t[hash].code); i++)
		hash = (sym + i) % N;
	return hash;
}



void inclusionSort(table *t)
{
	for (int i = 1; i < N; i++)
	{
		table *t2 = new table[1];
		t2[0] = t[i]; 
		int index = i, value = t[i].numb;     
		for (index; index > 0 && value < t[index - 1].numb; index--)
		{  
			t[index] = t[index - 1];
		}
		t[index] = t2[0]; 
	}
}

void bubbleSort(table *t)
{
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < N - i; j++)
		{
			if (t[j].numb > t[j + 1].numb) 
			{
				table *t2 = new table[1];
				t2[0] = t[j];
				t[j] = t[j + 1];
				t[j + 1] = t2[0];
				delete[] t2;
			}
		}
	}
}

void shellSort(table *t)               
{
	int d[9] = { 1, 4, 10, 23, 57, 132, 301, 701, 1750 }; // Последовательность Марцина Циура
	int k = 0;
	for (int step = d[k]; step > 0; step = d[k + 1])
	{     
		for (int i = step; i < N; i++) 
		{              
			for (int j = 0; j < i; j++) 
			{               
				if (t[j].numb > t[i].numb) 
				{        
					table *t2 = new table[1];
					t2[0] = t[j];
					t[j] = t[i];
					t[i] = t2[0];
				}
			}
		}
	}
}

void priceList(map <string, int> &tablePrice) // Таблица стоимости
{
	string codes;
	int price;
	ifstream file("A:\\price.txt");
	if (file.is_open())
	{
		for (file >> codes >> price; !file.eof(); file >> codes >> price)
			tablePrice.emplace(codes, price);
	}
	else
		printf_s("Файл не найден \n");
	file.close();
}


void inputPrice(table *t, map <string, int> tablePrice) // Помещение значений стоимости в объединённую таблицу
{
	for (int i = 0; i < N; i++)
	{
		for (auto it = tablePrice.begin(); it != tablePrice.end(); it++)
		{
			if (t[i].code == it->first)
				t[i].price = it->second;
		}
	}
}

void sortTa(map <string, itemField> &sortTable, table *t, int &num) // Упорядоченная таблица
{
	char name[255];
	int numb;
	int flag = 0;
	string codes;
	ifstream file1("A:\\work.txt");
	if (file1.is_open())
	{
		for (file1 >> codes >> name >> numb; !file1.eof(); file1 >> codes >> name >> numb)
		{
			flag = 0;
			for (auto it = sortTable.begin(); it != sortTable.end() && !flag; it++)
			{
				if (codes == it->first)
					it->second.numb += numb;
			}
			if (!flag)
			{
				itemField *t = new itemField[1];
				strcpy(t->name, name);
				t->numb = numb;
				sortTable.emplace(codes, *t);
				delete[] t;
				flag++;
			}
		}
	}
	else
		printf_s("Файл не найден \n");
	for (auto it = sortTable.begin(); it != sortTable.end(); it++) // Копирование из map в table для сортировки
	{
		char *code = new char[9];
		copy(it->first.begin(), it->first.end(), code);
		code[it->first.size()] = '\0';
		strcpy(t[num].code, code);
		strcpy(t[num].name, it->second.name);
		t[num].numb = it->second.numb;
		num++;
	}
}