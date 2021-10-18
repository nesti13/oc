#include <windows.h>
#include <iostream>
#include <tchar.h>

using namespace std;

HANDLE hHeap;
INT Size;
LPINT arr;

INT Create()
{
	setlocale(LC_CTYPE, "Russian");
	int num;
	cout << "Введите начальный размер массива:\t";
	cin >> Size;

	hHeap = HeapCreate(HEAP_NO_SERIALIZE, Size * sizeof(int), 0);
	if (!hHeap) {
		_tprintf_s(TEXT("Ошибка создания кучи: %d\n"), GetLastError());
		return EXIT_FAILURE;
	}
	else
		_tprintf_s(TEXT("Куча создана!\n"));
	arr = (LPINT)HeapAlloc(hHeap, NULL, Size * sizeof(int));//выделили память под N интов из кучи
	if (!arr) {
		_tprintf_s(TEXT("Ошибка выделения кучи: %d\n"), GetLastError());
	}
	else {
		cout << "Введите начальный массив\n";
		for (int i = 0; i < Size; i++) {
			cin >> num;
			arr[i] = num;
		}
	}


	return EXIT_SUCCESS;
}

INT AddRight() {
	INT num;
	Size++;
	arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, Size * sizeof(int));
	cout << "Введите номер\n";
	cin >> num;
	arr[Size - 1] = num;
	cout << "Куча перераспределена\n";
	return EXIT_SUCCESS;
}

INT DeleteLast() {
	Size--;
	arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, Size * sizeof(int));
	cout << "Удалено\n";
	return EXIT_SUCCESS;
}

INT DeleteOnPos() {
	int pos;
	cout << "Выберите позицию:\t";
	cin >> pos;
	pos--;
	for (int i = pos; i < Size - 1; i++) {
		arr[i] = arr[i + 1];

	}
	Size--;
	arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, Size * sizeof(int));
	return EXIT_SUCCESS;
}

INT Inject() {
	int pos, num;
	Size++;
	arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, Size * sizeof(int));
	cout << "Выберите позицию:\t";
	cin >> pos;
	cout << "Введите число, которое нужно добавить:\t";
	cin >> num;
	for (int i = Size - 1; i > pos - 1; i--) {
		arr[i] = arr[i - 1];
	}
	arr[pos - 1] = num;
	return EXIT_SUCCESS;
}

INT See() {
	cout << "Массив:\t";
	for (int i = 0; i < Size; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
	return EXIT_SUCCESS;
}

INT _tmain(INT argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	int n, c;
	while (true) {
		cout << "1. Создать кучу\n2. Добавить новый элемент в массив\n3. Удалить из массива элемент\n4. Вставить новый элемент в массив внутрь со сдвигом на один элемент вправо\n5. Удалить из массива один элемент внутри со сдвигом правой части влево\n6. Вывести массив\n";
		cout << "Ваш выбор:\t";
		cin >> c;
		switch (c) {
		case 1:Create(); break;
		case 2:AddRight(); break;
		case 3:DeleteLast(); break;
		case 4:Inject(); break;
		case 5:DeleteOnPos();
		case 6:See(); break;
		}
	}
	cout << "\n" << HeapSize(hHeap, NULL, arr) / sizeof(int);
	HeapDestroy(hHeap);
	cout << "Куча разрушена\n\n";
	_tsystem(TEXT("pause"));
	return EXIT_SUCCESS;
}
