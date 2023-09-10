#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define TIMER_SEC 1

#include "Windows.h"
#include <stdio.h>
#include <windowsx.h>
#include <Wingdi.h>
#include <sstream>
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"
#include "cmath"

HWND hwnd;
RECT Rect;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };

int t(0), r(0);
bool Back(false), Rotate(false);

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
		SetTimer(hWnd, TIMER_SEC, 15, NULL);
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_TIMER:
	{
		if (!Back)
			t += 5;
		else
			t -= 5;
		if (t > Rect.right && !Back)
			Back = true;
		if (t < 0 && Back)
			Back = false;
		
		InvalidateRect(hwnd, NULL, TRUE);

		break;
	}
	case WM_LBUTTONDOWN:
	{
		//double xM(LOWORD(lParam)), yM(HIWORD(lParam));
		//hDc = GetDC(hWnd);
		Rotate = true;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		GetClientRect(hWnd, &Rect);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HPEN PSpringGreen(CreatePen(PS_SOLID, 2, RGB(0, 250, 154)));
		HPEN PBlack(CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
		HBRUSH BSpringGreen(CreateSolidBrush(RGB(0, 250, 154)));

		SelectObject(hDc, BSpringGreen);
		SelectObject(hDc, PSpringGreen);

		Ellipse(hDc, t-50, Rect.bottom/2+sin(t * M_PI / 180)*50 + 50, t+50, Rect.bottom / 2+sin(t * M_PI / 180)*50 - 50);

		if (Rotate)
		{
			SelectObject(hDc, PBlack);
			MoveToEx(hDc, t, Rect.bottom / 2 + sin(t * M_PI / 180) * 50, NULL);
			LineTo(hDc, t - cos(t * M_PI / 180) * 100, Rect.bottom/2 - sin(t * M_PI / 180) * 100);
		}

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		DeleteObject(PBlack);
		DeleteObject(PSpringGreen);
		DeleteObject(BSpringGreen);

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
		KillTimer(hwnd, TIMER_SEC);
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

	hwnd = CreateWindow(WC.lpszClassName,L"Лабораторная работа WinApi №4", WS_OVERLAPPEDWINDOW,
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