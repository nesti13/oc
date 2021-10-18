#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>

using namespace std;
INT _tmain(INT argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, TEXT("Rus"));
	int c;
	while(true) {
		cout << "Выберите задание" << endl;
		cout << "1. Создать программно 2 каталога" << endl;
		cout << "2. В первом каталоге создать текстовый файл и записать в него текст" << endl;
		cout << "3. Скопировтаь созданный файл из первого каталога во второй" << endl;
		cout << "4. Удалить файл из первого каталога" << endl;
		cout << "5. Переименовать файл во втором каталоге и прочитать его содержимое" << endl;
		cin >> c;
		switch (c)
		{
		case 1: 
		{
			TCHAR Buffer1[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new1");
			TCHAR Buffer2[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new2");
			if (CreateDirectory(Buffer1, NULL) & CreateDirectory(Buffer2, NULL)) {
				_tprintf_s(TEXT("Directories created.\n"));
			}
			else {
				_tprintf_s(TEXT("Directories didn't created.\n"));
			}
		break;
		}
		case 2:
		{
			_tsetlocale(LC_ALL, TEXT("Rus"));
			TCHAR Buffer[] = TEXT("Thunder");
			HANDLE hOut;
			DWORD dwNumberOfBytes;
			TCHAR stdPath[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new1\\1.txt");
			hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hOut == INVALID_HANDLE_VALUE) {
				_tprintf_s(TEXT("Error: %x.\n"), GetLastError());
				return EXIT_FAILURE;
			}
			else
			{
				WriteFile(hOut, Buffer, sizeof(Buffer), &dwNumberOfBytes, NULL);
				_tprintf_s(TEXT("Created and Written!\n"));
				CloseHandle(hOut);
			}
			break;
		}
		case 3:
		{
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new1\\1.txt");
			TCHAR stdPathB[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new2\\2.txt");
			BOOL pr = CopyFile(stdPathA, stdPathB, 0);
			if (pr)
			{
				_tprintf_s(TEXT("Copied.\n"));
			}
			else
			{
				_tprintf_s(TEXT("Not copied.\n"));
			}
			break;
		}
		case 4:
		{
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new1\\1.txt");
			BOOL pr = DeleteFile(stdPathA);
			if (pr)
			{
				_tprintf_s(TEXT("Deleted.\n"));
			}
			else
			{
				_tprintf_s(TEXT("Not deleted.\n"));
			}
			break;
		}
		case 5:
		{
			HANDLE hOut;
			DWORD dwNumberOfBytes;
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new2\\2.txt");
			TCHAR stdPathB[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new2\\2a.txt");
			BOOL pr = MoveFile(stdPathA, stdPathB);
			if (pr)
			{
				_tprintf_s(TEXT("Renamed.\n"));
			}
			else
			{
				_tprintf_s(TEXT("Not renamed.\n"));
			}
			TCHAR readedInfo[256];
			hOut = CreateFile(TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\задание\\new2\\2a.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			ReadFile(hOut, readedInfo, sizeof(readedInfo), &dwNumberOfBytes, NULL);
			wcout << readedInfo << endl;
			CloseHandle(hOut);
			break;		
		}
		}
	} 
}