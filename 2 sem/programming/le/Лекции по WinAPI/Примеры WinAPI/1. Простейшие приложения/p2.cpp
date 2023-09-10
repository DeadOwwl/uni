#include <windows.h>
// 2 программа - простейшее Windows-приложение с циклом обработки сообщений
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE d2, LPSTR d3, int d4 )
{
	HWND hwnd;
	hwnd = CreateWindow( L"BUTTON", L"Hello, World!",
						WS_VISIBLE | BS_CENTER, 100, 100, 100, 80,
						NULL, NULL, hInstance, NULL );
	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) )
	{
		if ( msg.message == WM_LBUTTONUP )
		{
			DestroyWindow( hwnd );
			PostQuitMessage( 0 );
		}
		DispatchMessage( &msg );
	}
	return msg.wParam;
}

