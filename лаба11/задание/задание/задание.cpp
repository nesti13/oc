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
	setlocale(LC_CTYPE, "Russian");
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

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);

	if (IsProcessRun(TEXT(" ")))
		_tprintf_s(TEXT("Running.\n"));
	else
		_tprintf_s(TEXT("Not running.\n"));

	_tsystem(TEXT("pause"));
	return EXIT_SUCCESS;
}