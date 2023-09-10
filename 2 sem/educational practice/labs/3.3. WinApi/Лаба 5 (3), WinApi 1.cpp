#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"

HWND hwnd;
RECT Rect;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
static int incrDecr(1), fCh(17), idX(0), idY(0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	PAINTSTRUCT PS;
	GetClientRect(hwnd, &Rect);
	switch (uMsg)
	{
	case WM_SIZE:
	{
		InvalidateRect(hwnd, NULL, true);
		break;
	}
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HFONT MFont(CreateFont((200 + incrDecr)/12, ((200 + incrDecr) / 12)/1.5, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Georgia"));

		HPEN PWhite = CreatePen(PS_SOLID, 2, RGB(255,255,255));
		HBRUSH BBlack = CreateSolidBrush(RGB(0,0,0));
		SelectObject(hDc, PWhite);
		SelectObject(hDc, BBlack);
		SelectObject(hDc, MFont);
		POINT Triangle[3];
		Triangle[0].x = Rect.right;
		Triangle[0].y = Rect.bottom-200 - incrDecr;
		Triangle[1].x = Rect.right;
		Triangle[1].y = Rect.bottom;
		Triangle[2].x = Rect.right-200 - incrDecr;
		Triangle[2].y = Rect.bottom;
		Polygon(hDc, Triangle, 3);
		FillRgn(hDc, (HRGN)Triangle, (HBRUSH)BLACK_BRUSH);

		TextOut(hDc, Rect.right-(180 + incrDecr) / 2, Rect.bottom-(200+incrDecr)/2, L"Kragel", 7);

		EndPaint(hwnd, &PS);

		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ADD:
		{
			incrDecr += 5;

			InvalidateRect(hWnd, NULL, true);
			break;
		}
		case VK_SUBTRACT:
		{
			incrDecr -= 5;
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		}
		break;
	}
	case WM_CLOSE:
	{
		if (IDYES == MessageBox(hWnd, L"Желаете закрыть приложение?", L"Запрос о закрытии", MB_YESNO | MB_ICONQUESTION))
			DestroyWindow(hWnd);
		return EXIT_SUCCESS;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	return EXIT_SUCCESS;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LCmdShow, int nCmdShow)
{
	MSG msg;
	WC.style = CS_VREDRAW | CS_HREDRAW;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = hInstance;
	WC.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0)));
	WC.lpszMenuName = NULL;
	WC.lpszClassName = L"Лабораторная работа WinApi №3";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба №3", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, L"Лабораторная работа WinApi №3", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"Ошибка создания главного окна", L"Ошибка WinApi. Лаба №3", MB_OK);
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}