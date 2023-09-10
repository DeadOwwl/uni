#include <windows.h>

// 1 программа - простейшее Windows-приложение
int WINAPI WinMain (HINSTANCE d1, HINSTANCE d2, LPSTR d3, int d4)
{
	MessageBox(NULL, L"Hello, World!", L"", MB_OK);
	return 0;
}

