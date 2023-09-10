#include <windows.h>

void AddSegmentAtMessagePos( HDC hDC, HWND hwnd, BOOL bDraw )
{
	DWORD dwPos;
	POINTS points;
	POINT point;
	dwPos = GetMessagePos();
	points = MAKEPOINTS( dwPos );
	point.x = points.x;
	point.y = points.y;
	ScreenToClient( hwnd, &point );
	DPtoLP( hDC, &point, 1 );

	if ( bDraw )
		LineTo( hDC, point.x, point.y );
	else
		MoveToEx( hDC, point.x, point.y, NULL );
}

void DrawHello( HWND hwnd )
{
	if ( GetCapture() != NULL )
		return;
	
	HDC hDC = GetDC( hwnd );
	if ( hDC != NULL )
	{
		SetCapture( hwnd );
		AddSegmentAtMessagePos( hDC, hwnd, FALSE );
		
		MSG msg;
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			if ( GetCapture() != hwnd )
				break;
	
			switch ( msg.message )
			{
				case WM_MOUSEMOVE :
				AddSegmentAtMessagePos( hDC, hwnd, TRUE );
				break;
				case WM_LBUTTONUP:
				goto ExitLoop;
				default:
				DispatchMessage( &msg );
			}
		}
		
ExitLoop:
		ReleaseCapture();
		ReleaseDC( hwnd, hDC );
	}
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_LBUTTONDOWN : DrawHello( hwnd ); break;
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
		memset( &wndClass, 0, sizeof( wndClass ) );
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = hInstance;
		wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.lpszClassName = L"HELLO";
		if ( !RegisterClass( &wndClass ) )
			return FALSE;
	}
	
	HWND hwnd;
	hwnd = CreateWindow( L"HELLO", L"HELLO", WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
						NULL, NULL, hInstance, NULL);
	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );

	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) )
		DispatchMessage( &msg );
	return msg.wParam;
}
