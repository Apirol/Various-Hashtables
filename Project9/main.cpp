#include <stdio.h>
#include "head.h"
#include <conio.h>
#include <locale.h>
#include <map>

using namespace std;
int num = 0;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int exitFlag = 0, n, numb;
	char name[255], code[9];
	table *t = new table[N];
	for (int i = 0; i < N; i++)
	{
		t[i].code[0] = '\0';
		t[i].name[0] = '\0';
		t[i].numb = 0;
		t[i].price = 0;
	}
	map <string, itemField> sortTable;
	map <string, int> tablePrice;
	priceList(tablePrice);
	FILE *f;
	errno_t err = fopen_s(&f, "A://work.txt", "r");
	if (!err)
	{
		do
		{
			printf_s("<1> - сортировка упорядоченной таблицы методом прямого обмена \n");
			printf_s("<2> - сортировка упорядоченной таблицы методом прямого включения \n");
			printf_s("<3> - сортировка упорядоченной таблицы методом Шелла \n");
			printf_s("<4> - сортировка хеш-таблицы методом прямого обмена \n");
			printf_s("<5> - сортировка хеш-таблицы методом прямого включения \n");
			printf_s("<6> - сортировка хеш-таблицы методом Шелла \n");
			printf_s("<7> - выход \n");
			int repeatFlag = 0;
			do
			{
				printf_s("Введите номер команды (от 1 до 7) \n");
				if (!scanf_s("%d", &n))
				{
					printf_s("Ошибка \n");
					_getch();
					return 0;
				}
				switch (n)
				{
				case 1:
					sortTa(sortTable, t, num);
					inputPrice(t, tablePrice);
					bubbleSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
				case 2: 
					sortTa(sortTable, t, num);
					inputPrice(t, tablePrice);
					inclusionSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
				case 3: sortTa(sortTable, t, num);
					inputPrice(t, tablePrice);
					shellSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
				case 4: f = fopen("A://work.txt", "r");
					while (fscanf(f, "%s %s %i", code, name, &numb) != EOF && num < N)
						hashTable_add(t, code, name, numb);
					inputPrice(t, tablePrice);
					bubbleSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
					break;
				case 5: f = fopen("A://work.txt", "r");
					while (fscanf(f, "%s %s %i", code, name, &numb) != EOF && num < N)
						hashTable_add(t, code, name, numb);
					inputPrice(t, tablePrice);
					inclusionSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
				case 6: f = fopen("A://work.txt", "r");
					while (fscanf(f, "%s %s %i", code, name, &numb) != EOF && num < N)
						hashTable_add(t, code, name, numb);
					inputPrice(t, tablePrice);
					shellSort(t);
					f = fopen("A://table.txt", "w");
					for (int i = 0; i < N; i++)
						if (t[i].code[0] != '\0')
							fprintf(f, "%s\t%s\t%i\t%i\n", t[i].code, t[i].name, t[i].numb, t[i].price);
					delete[] t;
					++exitFlag;
					break;
				case 7: exitFlag = 1;
					break;
				default: printf_s("Ошибка ввода операции \n");
					repeatFlag = 1;
					break;
				}
			} while (!exitFlag && !repeatFlag);
		} while (!exitFlag);
	}
	else
		printf_s("Файл work.txt не найден \n");
	fcloseall();
   return 0;
}