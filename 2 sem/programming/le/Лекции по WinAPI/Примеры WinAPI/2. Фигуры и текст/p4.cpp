#include <windows.h>
//
// 3 программа - простейшее Windows-приложение с циклом обработки сообщений
//               и собственныи оконным классом
void DrawHello( HWND hwnd )
{
	PAINTSTRUCT paintStruct;
	HDC hDC = BeginPaint( hwnd, &paintStruct );
	if ( hDC != NULL )
	{
		RECT clientRect;
		GetClientRect( hwnd, &clientRect );
		DPtoLP( hDC, (LPPOINT)&clientRect, 2 );
		DrawText( hDC, L"Hello, World!", -1, &clientRect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		EndPaint( hwnd, &paintStruct );
	}
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_PAINT : DrawHello( hwnd ); break;
	case WM_DESTROY : PostQuitMessage( 0 ); break;
	default : return DefWindowProc( hwnd, uMsg, wParam, lParam );
	}
	return 0;
}
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR d3, int nCmdShow )
{
	if ( hPrevInstance == NULL )
	{
		WNDCLASS wndClass;
		memset( &wndClass, 0, sizeof(wndClass) );
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = hInstance;
		wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
		wndClass.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
		wndClass.lpszClassName = L"HELLO";
		if ( !RegisterClass( &wndClass ) )
			return FALSE;
	}
	HWND hwnd;
	hwnd = CreateWindow(L"HELLO", L"HELLO", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
						NULL, NULL, hInstance, NULL );
	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );
	
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) )
		DispatchMessage( &msg );
	
	return msg.wParam;
}