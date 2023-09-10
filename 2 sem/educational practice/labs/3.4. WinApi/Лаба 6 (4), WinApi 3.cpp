#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define TIMER_SEC 1

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"
#include "cmath"

HWND hwnd;
RECT Rect;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
static int cF(0), cS(0), cT(0);
static bool fFigure(false), sFigure(false), tFigure(false);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	PAINTSTRUCT PS;
	GetClientRect(hwnd, &Rect);

	COLORREF fColor(RGB(255, 255, 240)), sColor(RGB(255, 235, 215)), tColor(RGB(255, 222, 173));
	int x(LOWORD(lParam)), y(HIWORD(lParam));

	switch (uMsg)
	{
	case WM_SIZE:
	{
		InvalidateRect(hwnd, NULL, true);
		break;
	}
	case WM_CREATE:
	{
		SetTimer(hWnd, TIMER_SEC, 50, NULL);
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_LBUTTONDOWN:
	{
		hDc = GetDC(hWnd);
		COLORREF S = GetPixel(hDc, x, y);
		if (GetPixel(hDc, x, y) == fColor)
			fFigure = true;
		if (GetPixel(hDc, x, y) == sColor)
			sFigure = true;
		if (GetPixel(hDc, x, y) == tColor)
			tFigure = true;
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	}
    case WM_RBUTTONDOWN:
	{
		hDc = GetDC(hWnd);
		if (GetPixel(hDc, x, y) == fColor)
			fFigure = false;
		if (GetPixel(hDc, x, y) == sColor)
			sFigure = false;
		if (GetPixel(hDc, x, y) == tColor)
			tFigure = false;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_TIMER:
	{
		if (fFigure)
			if (cF == 0)
				cF += 5;
			else
				if (cF == 5)
					cF -= 5;
		if (sFigure)
			if (cS == 0)
				cS += 10;
			else
				if (cS == 10)
					cS -= 10;
		if (tFigure)
			if (cT == 0)
				cT += 15;
			else
				if (cT == 15)
					cT -= 15;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HBRUSH fBrush(CreateSolidBrush(RGB(255, 255, 240)));
		HBRUSH sBrush(CreateSolidBrush(RGB(255, 235, 215)));
		HBRUSH tBrush(CreateSolidBrush(RGB(255, 222, 173)));

		HPEN fPen(CreatePen(PS_SOLID, 1, RGB(255, 255, 240)));
		HPEN sPen(CreatePen(PS_SOLID, 1, RGB(255, 235, 215)));
		HPEN tPen(CreatePen(PS_SOLID, 1, RGB(255, 222, 173)));

		POINT Figure[3];

		SelectObject(hDc, fBrush);
		SelectObject(hDc, fPen);
		Figure[0].x = Rect.left + 50-cF;
		Figure[0].y = Rect.bottom * 2 / 3 + cF;
		Figure[1].x = Rect.left + 50 - cF;
		Figure[1].y = Rect.bottom / 3 - cF;
		Figure[2].x = Rect.right / 4 - 50 + cF;
		Figure[2].y = Rect.bottom * 2 / 3 + cF;
		Polygon(hDc, Figure, 3);

		SelectObject(hDc, sBrush);
		SelectObject(hDc, sPen);
		Figure[0].x = Rect.right/2 - 100 - cS;
		Figure[0].y = Rect.bottom * 2 / 3 + cS;
		Figure[1].x = Rect.right/2 + 100 + cS;
		Figure[1].y = Rect.bottom *2/ 3 + cS;
		Figure[2].x = Rect.right / 2;
		Figure[2].y = Rect.bottom / 3 - cS;
		Polygon(hDc, Figure, 3);

		SelectObject(hDc, tBrush);
		SelectObject(hDc, tPen);
		Figure[0].x = Rect.right - 50 + cT;
		Figure[0].y = Rect.bottom * 2 / 3 + cT;
		Figure[1].x = Rect.right - 50 + cT;
		Figure[1].y = Rect.bottom / 3 - cT;
		Figure[2].x = Rect.right *3/ 4 + 50 - cT;
		Figure[2].y = Rect.bottom *2/ 3 + cT;
		Polygon(hDc, Figure, 3);

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		DeleteObject(fBrush);
		DeleteObject(sBrush);
		DeleteObject(tBrush);
		DeleteObject(fPen);
		DeleteObject(sPen);
		DeleteObject(tPen);

		EndPaint(hwnd, &PS);

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

		KillTimer(hWnd, 1);
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
	WC.lpszClassName = L"Лабораторная работа WinApi №4";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба №4", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, L"Лабораторная работа WinApi №4", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"Ошибка создания главного окна", L"Ошибка WinApi. Лаба №4", MB_OK);
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