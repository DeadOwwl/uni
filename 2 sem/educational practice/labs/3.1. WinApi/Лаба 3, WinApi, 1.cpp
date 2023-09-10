#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpstrCmdLine, int nCmdShow)
{
	LPWSTR* lP;
	int c(nCmdShow);
	lP = CommandLineToArgvW(GetCommandLine(), &c);
	MessageBox(NULL,lP[1], L"Hi!", MB_OK);
	return 0;
}