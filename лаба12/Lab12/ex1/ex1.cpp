#include <windows.h>
#include "string.h"
#include <iostream>
using namespace std;

DWORD WINAPI myThread_1(LPVOID lpParameter)
{
	unsigned int numb1 = 0;
	while (numb1 < 60)
	{
		Sleep(500);
		numb1++;
		cout << numb1 << endl;
	}
	return 0;
}

DWORD WINAPI myThread_2(LPVOID lpParameter)
{
	unsigned int numb2 = 100;
	while (numb2 > 0)
	{
		Sleep(500);
		numb2--;
		cout << numb2 << endl;
	}
	return 0;
}

int main()
{
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle1 = CreateThread(0, 0, myThread_1, &myCounter, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, myThread_2, &myCounter, 0, &myThreadID);
	Sleep(20000);
	printf("\n The end");
	TerminateThread(myHandle1, 0);
	TerminateThread(myHandle2, 0);
	getchar();

	return 0;
}