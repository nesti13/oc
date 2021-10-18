#include <windows.h>
#include <tchar.h> 

DWORD Number; 

DWORD WINAPI Reader(LPVOID lpparameter) 
{
	_tprintf_s(TEXT("Counter= %d\n"), Number); 
	return 0;
}

DWORD WINAPI Writer(LPVOID lpParameter) { 
	unsigned int counter = 0;
	DWORD dwMyThreadID1;

	while (counter != 10) {
		Number = counter; 
		HANDLE hMyHandle2 = CreateThread(NULL, 0, Reader, 0, 0, &dwMyThreadID1);
		Sleep(300); 
		TerminateThread(hMyHandle2, 0); 
		counter++; 
	}

	return EXIT_SUCCESS;
}

INT _tmain(INT argc, _TCHAR* argv[]) {
	DWORD dwMyThreadID;
	HANDLE hMyHandle = CreateThread(NULL, 0, Writer, 0, 0, &dwMyThreadID);
	Sleep(5000);
	_tprintf_s(TEXT("Main Process end\n"));
	TerminateThread(hMyHandle, 0);
	_tsystem(TEXT("pause"));
	return EXIT_SUCCESS;
}