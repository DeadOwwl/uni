#include <windows.h>
//
// ׀אבמעא סמ רנטפעמל
//
void DrawHello( HWND hwnd )
{
	PAINTSTRUCT paintStruct;
	HFONT hFont;
	static LOGFONT lf;
	HDC hDC = BeginPaint( hwnd, &paintStruct );
	if ( hDC != NULL )
	{
		lf.lfItalic = TRUE;
		lf.lfWeight = FW_BOLD;
		lf.lfHeight = 40;
		lstrcpy((LPSTR)&lf.lfFaceName,"Arial");
		hFont =CreateFontIndirect(&lf);
		SelectObject(hDC,(HFONT)hFont);
		SetTextColor(hDC,RGB(0,0,0xFF));
		TextOut(hDC, 10, 10, "Hello, World!", 13);
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
		wndClass.lpszClassName = "HELLO";
		if ( !RegisterClass( &wndClass ) )
			return FALSE;
	}
	HWND hwnd;
	hwnd = CreateWindow("HELLO", "HELLO", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
						NULL, NULL, hInstance, NULL );
	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );
	
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) )
		DispatchMessage( &msg );
	
	return msg.wParam;
}