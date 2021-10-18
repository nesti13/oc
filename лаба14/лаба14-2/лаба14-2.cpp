#include<tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	HANDLE hslot;
	TCHAR slotname[] = TEXT("\\\\.\\mailslot\\demoslot");
	hslot = CreateMailslot(slotname, 0, MAILSLOT_WAIT_FOREVER, NULL);// имя, максимальный размер, интервал-тайм аута чтения, информация о безопасности

	if (hslot == INVALID_HANDLE_VALUE)
	{
		cout << "Fail" << endl;
		cout << "Finish" << endl;
		cin.get();
		return 0;
	}

	cout << "Waiting" << endl;

	char text2[20], text[20];
	DWORD dwBytesRead;

	ReadFile(hslot, text2, sizeof(text2), &dwBytesRead, (LPOVERLAPPED)NULL);
	Sleep(3000);
	ReadFile(hslot, text, sizeof(text), &dwBytesRead, (LPOVERLAPPED)NULL);

	cout << "Данные: " << text2 << text << endl;

	CloseHandle(hslot);
	cin.get();
	return 0;
}