#include <windows.h>
#include <iostream>
#include "string.h"

CRITICAL_SECTION cs;					
TCHAR stdPath[50] = TEXT("C:\\Users\\Admin\\Desktop\\оси\\лаба13\\Lab13\\1.txt");

HANDLE hOut;
DWORD dwBytes;
FILE* fp;
HANDLE hIn;

DWORD WINAPI myThread(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;				

	EnterCriticalSection(&cs);		
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("ERROR WRITING FILE");
		return 2;
	}
	else

	{
		WriteFile(hOut, b, 256, &dwBytes, NULL); 
		printf("First thread written\n");
		CloseHandle(hOut);
	}

	LeaveCriticalSection(&cs);    
	return 0;

}


DWORD WINAPI myThread2(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;

	TCHAR Bu[255];

	EnterCriticalSection(&cs);

	hIn = CreateFile(stdPath, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hIn == INVALID_HANDLE_VALUE)
	{
		printf("Error");
		return 2;
	}
	else
	{
		ReadFile(hIn, Bu, 256, &dwBytes, NULL);

		printf("Second thread read\n");
		std::wcout << "Read: " << Bu << '\n';
		CloseHandle(hIn);

	}
	LeaveCriticalSection(&cs);
	return 0;

}

int main(int argc, TCHAR* argv[])
{


	int z = 0;

	DWORD myThreadID;
	DWORD myThreadID2;

	TCHAR Buff[256] = TEXT("Hallo!");
	TCHAR Buff2[256];

	InitializeCriticalSection(&cs);

	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)Buff, CREATE_SUSPENDED, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, myThread2, (void*)Buff2, CREATE_SUSPENDED, &myThreadID2);


	BOOL b = SetThreadPriorityBoost(myHandle, false); 

	if (b)
	{
		SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST);

	}

	ResumeThread(myHandle);
	ResumeThread(myHandle2);
	WaitForSingleObject(myHandle, 10000);	
	WaitForSingleObject(myHandle2, 10000);
	

	TerminateThread(myHandle, 0);
	TerminateThread(myHandle2, 0);

	getchar();

	return 0;
}