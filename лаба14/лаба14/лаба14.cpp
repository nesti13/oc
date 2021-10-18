#include<iostream>
#include<windows.h>
#include<string.h>
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

struct book
{
	char title[10];
};

void main() 
{
	setlocale(LC_CTYPE, "Russian");
	int c;
	while (true) {
		cout << "Выберите:" << endl;
		cout << "1.Создать массив для размещения строк" << endl;
		cout << "2.Создать массив для размещения структуры" << endl;
		cout << "3.Создать массив для размещения массива структур" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
		{
			system("mode con cols=60 lines=10");
			SetConsoleTextAttribute(hStdOut, 11);
			int size;
			char** arr;
			cout << "Введите размер массва : ";
			cin >> size;

			arr = (char**)malloc(size * sizeof(char*));

			if (!arr)
			{
				cout << "Ошибка";
				return;
			}

			for (int i = 0; i < size; i++)
			{
				arr[i] = (char*)malloc(50 * sizeof(char));
				cin >> arr[i];
			}
			cout << endl;

			cout << "Вывод элементов массва : ";
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			free(arr);
			cout << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			system("mode con cols=60 lines=10");
			SetConsoleTextAttribute(hStdOut, 11);
			int size;
			book* arr;

			cout << "Введите размер :";
			cin >> size;

			arr = (book*)malloc(size * sizeof(book));

			if (!arr)
			{
				cout << "Ошибка";
				return;
			}

			cout << "Ввод элементов : " << endl;
			for (int i = 0; i < size; i++)
			{
				cin >> arr[i].title;
			}

			cout << endl;
			cout << "Вывод элементов : " << endl;
			for (int i = 0; i < size; i++)
			{
				cout << arr[i].title << endl;
			}
			free(arr);
			cout << endl;
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			system("mode con cols=60 lines=10");
			SetConsoleTextAttribute(hStdOut, 11);
			int size;
			book** arr;
			cout << "Введите размер: ";
			cin >> size;

			arr = (book**)malloc(size * sizeof(book*));

			if (!arr)
			{
				cout << "Ошибка";
				return;
			}

			cout << "Ввод элементов: " << endl;
			for (int i = 0; i < size; i++)
			{
				*(arr + i) = (book*)malloc(size * sizeof(book));
				for (int j = 0; j < size; j++)
				{
					cin >> arr[i][j].title;
				}
			}

			cout << endl;
			cout << "Вывод элементов: " << endl;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << arr[i][j].title << endl;
				}
			}
			free(arr);
			system("pause");
			break;
		}
		}
	}
}