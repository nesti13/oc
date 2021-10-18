#include<tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	HANDLE hslot;

	TCHAR slotname[] = TEXT("\\\\.\\mailslot\\demoslot");
	hslot = CreateFile(slotname, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);// имя, режим доступа, совместный доступ, дескр защ, атрибуты файлы, дескр.шаблона файла


	if (hslot == INVALID_HANDLE_VALUE)
	{
		cout << "Fail" << endl;
		cout << "Finish" << endl;
		cin.get();
		return 0;
	}

	cout << "The first client: " << endl;
	char text[8] = "Client1";
	DWORD dwBytesWrite;

	WriteFile(hslot, text, sizeof(text), &dwBytesWrite, NULL);

	cout << "Данные: " << text << endl;

	CloseHandle(hslot);
	cin.get();
	return 0;
}