#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include <tlhelp32.h>
#include <tchar.h>
#include <fstream>
#include <stdio.h>
#include <locale.h>

using namespace std;

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)

bool AreEqual(const TCHAR* a, const TCHAR* b)
{
	while (*a == *b)
	{
		if (*a == _TEXT('\0'))
			return true;
		a++;
		b++;
	}
	return false;
}

bool IsProcessRun(const TCHAR* procName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);

	if (AreEqual(pe.szExeFile, procName))
	{
		return true;
	}

	while (Process32Next(hSnapshot, &pe))
	{
		if (AreEqual(pe.szExeFile, procName))
		{
			return true;
		}
	}
	return false;
}

INT _tmain(INT argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, TEXT("Rus"));
	int c;
	while (true) {
		cout << "Выберите:" << endl;
		cout << "1.Поиск файла(-ов) по имени" << endl;
		cout << "2.Запуск внешнего процесса Win API CreateProcess" << endl;
		cout << "3.Объединенный 1А и 1Б" << endl;
		cout << "4.Запуск процесса с выводом на консоль его системного номера (заголовка)" << endl;
		cout << "5.Запуск процесса из консоли с удалением консольного окна через 0.2 секунды" << endl;
		cout << "6.Вывод имен всех запущенных процессов" << endl;
		cout << "7.Проверка, выролняется ли процесс" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
		{
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind = INVALID_HANDLE_VALUE;

			TCHAR directorySearch[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба11\\примеры\\*");
			TCHAR filesearch[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба11\\примеры\\dat*.txt");
			// Find the first file in the directory.
			hFind = FindFirstFile(filesearch, &FindFileData);

			if (hFind == INVALID_HANDLE_VALUE)
			{
				_tprintf_s(TEXT("Invalid file handle. Error is %u.\n"), GetLastError());
			}
			else
			{
				_tprintf_s(TEXT("Found: %s\n"), FindFileData.cFileName);

				// List all the other files in the directory.
				while (FindNextFile(hFind, &FindFileData) != NULL)
				{
					_tprintf_s(TEXT("Found: %s\n"), FindFileData.cFileName);
				}
				FindClose(hFind);
			}
			break;
		}
		case 2:
		{
			STARTUPINFO cif;
			ZeroMemory(&cif, sizeof(STARTUPINFO));
			PROCESS_INFORMATION pi;
			TCHAR buf[] = TEXT("mspaint.exe");

			if (!CreateProcess(NULL, buf, NULL, NULL, FALSE, NULL,
				NULL, NULL, &cif, &pi)) {
				_tprintf_s(TEXT("Error.\n"));
			}
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		}
		case 3:
		{
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind = INVALID_HANDLE_VALUE;

			TCHAR directorySearch[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры\\пример2\\Debug\\");
			TCHAR filesearch[] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба10\\примеры\\пример2\\Debug\\пример*.exe");
			hFind = FindFirstFile(filesearch, &FindFileData);
				_tprintf_s(TEXT("Found: %s\n"), FindFileData.cFileName);
				TCHAR procName[MAX_PATH] = TEXT("");
				wcscpy_s(procName, directorySearch);
				wcscat_s(procName, FindFileData.cFileName);
				STARTUPINFO cif;
				ZeroMemory(&cif, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				if (!CreateProcess(procName, NULL, NULL, NULL, FALSE,
					0, NULL, NULL, &cif, &pi)) {
					_tprintf_s(TEXT("Error"), GetLastError());
				}
				FindClose(hFind);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			break;
		}
		case 4:
		{
			DWORD processID;
			STARTUPINFO cif;
			ZeroMemory(&cif, sizeof(STARTUPINFO));
			PROCESS_INFORMATION pi;
			TCHAR buf[] = TEXT("mspaint.exe");

			processID = CreateProcess(NULL, buf, NULL, NULL, FALSE, NULL,
				NULL, NULL, &cif, &pi);

			_tprintf_s(TEXT("Running with PID: %d.\n"), pi.dwProcessId);

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		}
		case 5:
		{
			STARTUPINFO cif;
			ZeroMemory(&cif, sizeof(STARTUPINFO));
			PROCESS_INFORMATION pi;
			TCHAR buf[] = TEXT("mspaint.exe");

			if (!CreateProcess(NULL, buf, NULL, NULL, FALSE, NULL,
				NULL, NULL, &cif, &pi)) {
				_tprintf_s(TEXT("Not running.\n"));
			}
			_tprintf_s(TEXT("Running.\n"));

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);

			HANDLE hProcess = GetCurrentProcess(); //получаем pID консольного приложен.

			if (NULL != hProcess)
			{
				Sleep(200);
				BOOL result = TerminateProcess(hProcess, EXIT_SUCCESS);

				CloseHandle(hProcess);
			}
			else
			{
				_tprintf_s(TEXT("Error when terminating.\n"));
			}
			break;
		}
		case 6:
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN |
				FOREGROUND_INTENSITY | BACKGROUND_BLUE);

			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hSnapshot) {
				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if (Process32First(hSnapshot, &pe32)) {
					do {
						_tprintf_s(TEXT("Running ProcName: %s.\n"), pe32.szExeFile);
					} while (Process32Next(hSnapshot, &pe32));
				}
				CloseHandle(hSnapshot);
			}

			CloseHandle(hStdout);
			break;
		}
		case 7:
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);

			if (IsProcessRun(TEXT("mspaint.exe")))
				_tprintf_s(TEXT("Running.\n"));
			else
				_tprintf_s(TEXT("Not running.\n"));
		break;
		}
		}
	}
}