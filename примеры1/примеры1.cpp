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
	while (true) {
		cout << "Выберите:" << endl;
		cout << "1.Пример1" << endl;
		cout << "2.Пример2" << endl;
		cout << "3.Пример3" << endl;
		cout << "4.Пример4" << endl;
		cout << "5.Пример5" << endl;
		cout << "6.Пример6" << endl;
		cout << "7.Пример7" << endl;
		cout << "8.Пример8" << endl;
		cout << "9.Пример9" << endl;
		cout << "10.Пример10" << endl;
		cout << "11.Пример11" << endl;
		cout << "12.Пример12" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
		{
			FILE* fp;
			TCHAR str[80];
			if ((fp = _tfopen(TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\1.txt"), TEXT("rt"))) == NULL)
			{
				_tprintf_s(TEXT("Opening failed\n"), str);
			}
			else
			{
				_fgetts(str, sizeof(str) / sizeof(TCHAR), fp);
				_tprintf_s(TEXT("read: %s\n"), str);
				INT z = fclose(fp);
			}
			break;
		}
		case 2:
		{
			FILE* fp;
			TCHAR str[] = TEXT("Hello World! Привет Мир!");
			TCHAR str2[80];
			if ((fp = _tfopen(TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\2.txt"), TEXT("wt"))) == NULL)
			{
				_putts(TEXT("Opening failed"));
			}
			else
			{
				_fputts(str, fp);
				INT z = fclose(fp);

				fp = _tfopen(TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\2.txt"), TEXT("rt"));
				_fgetts(str2, sizeof(str2) / sizeof(TCHAR), fp);
				_tprintf_s(TEXT("read: %s\n"), str2);
				z = fclose(fp);
			}
			break;
		}
		case 3:
		{
			HANDLE hOut;
			TCHAR stdPath[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\3.txt");

			hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hOut == INVALID_HANDLE_VALUE) {
				_tprintf_s(TEXT("Error: %x.\n"), GetLastError());
				return EXIT_FAILURE;
			}
			else
			{
				_tprintf_s(TEXT("Created.\n"));
				_tsystem(TEXT("pause"));
				CloseHandle(hOut);
			}
			break;
		}
		case 4:
		{
			TCHAR Buffer[] = TEXT("Glad to hear from You! Привет Мир!");
			HANDLE hOut;
			DWORD dwNumberOfBytes;

			TCHAR stdPath[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\4.txt");
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
				_tsystem(TEXT("pause"));
				CloseHandle(hOut);
			}
			break;
		}
		case 5:
		{
			TCHAR Buffer[256];
			HANDLE hIn;
			DWORD dwNumberOfBytes;

			TCHAR stdPath[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\4.txt");

			hIn = CreateFile(stdPath, GENERIC_READ, 0, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hIn == INVALID_HANDLE_VALUE) {
				_tprintf_s(TEXT("Error: %x.\n"), GetLastError());
				return EXIT_FAILURE;
			}
			else
			{
				ReadFile(hIn, Buffer, sizeof(Buffer), &dwNumberOfBytes, NULL);
				_tprintf_s(TEXT("Data read: %s\n"), Buffer);
				_tsystem(TEXT("pause"));
				CloseHandle(hIn);
			}
			break;
		}
		case 6:
		{
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\4.txt");
			TCHAR stdPathB[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\5.txt");

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
		case 7:
		{TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\1.txt");
		TCHAR stdPathB[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\1.txt");

		BOOL pr = MoveFile(stdPathA, stdPathB);
		if (pr)
		{
			_tprintf_s(TEXT("Moved.\n"));
		}
		else
		{
			_tprintf_s(TEXT("Not moved.\n"));
		}
			break;
		}
		case 8:
		{
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\2.txt");

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
		case 9:
		{
			TCHAR stdPathA[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\3.txt");
			TCHAR stdPathB[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\1а.txt");

			BOOL pr = MoveFile(stdPathA, stdPathB);
			if (pr)
			{
				_tprintf_s(TEXT("Renamed.\n"));
			}
			else
			{
				_tprintf_s(TEXT("Not renamed.\n"));
			}
			break;
		}
		case 10:
		{
			TCHAR Buffer[MAX_PATH];
			DWORD dwResult = GetCurrentDirectory(MAX_PATH, Buffer);
			_tprintf_s(TEXT("Dir: %s.\n"), Buffer);
			break;
		}
		case 11:
		{
			TCHAR Buffer[MAX_PATH];
			TCHAR Buffer2[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10");

			DWORD dwResult = GetCurrentDirectory(MAX_PATH, Buffer);
			_tprintf_s(TEXT("Dir: %s.\n"), Buffer);

			BOOL b = SetCurrentDirectory(Buffer2);

			dwResult = GetCurrentDirectory(MAX_PATH, Buffer);
			_tprintf_s(TEXT("Dir: %s.\n"), Buffer);
			break;
		}
		case 12:
		{
			TCHAR Buffer[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры1\\new");

			if (CreateDirectory(Buffer, NULL)) {
				_tprintf_s(TEXT("Directory created.\n"));
			}
			else {
				_tprintf_s(TEXT("Directory didn't created.\n"));
			}
			break;
		}
		}
	}
}