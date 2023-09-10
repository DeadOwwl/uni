#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define TIMER_SEC 1
#undef UNICODE

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

using namespace std;

HWND hwnd;
RECT Rect;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };

double F1(double x) {
	return 2*x;
}

double F2(double x) {
	return pow(x, 2);
}

double F3(double x) {
	return 2*log(x);
}

int t(0);
bool Click(false), fFunc(true), sFunc(false), tFunc(false);
static POINT Point;
COLORREF fColor(RGB(255, 255, 255));

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
		SetTimer(hWnd, TIMER_SEC, 1000, NULL);
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_TIMER:
	{
		t++;
		if (t % 7  == 0 && fFunc)
		{
			t = 0;
			fFunc = false;
			sFunc = true;
			tFunc = false;
		}
		else
		if (t % 7 == 0 && sFunc)
		{
			t = 0;
			fFunc = false;
			sFunc = false;
			tFunc = true;
		}
		else
		if (t % 7 == 0 && tFunc)
		{
			t = 0;
			fFunc = true;
			sFunc = false;
			tFunc = false;
		}
		InvalidateRect(hwnd, NULL, TRUE);

		break;
	}
	case WM_LBUTTONDOWN:
	{
		GetCursorPos(&Point);
		ScreenToClient(hWnd, &Point);
		double x(LOWORD(lParam)), y(HIWORD(lParam));
		hDc = GetDC(hWnd);
		if (GetPixel(hDc, x, y) != RGB(255, 255, 255))
			Click = false;
		else 
			Click = true;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		GetClientRect(hWnd, &Rect);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		DrawText(hDc, "made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		const int xVe(Rect.right - Rect.left), yVe(Rect.bottom - Rect.top);

		double StepX(Rect.right / 200), StepY(Rect.bottom/100);
		HFONT MFont(CreateFontW(40, 10, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, L"Gabriola"));
		HPEN PWhite(CreatePen(PS_SOLID, 4, RGB(255, 255, 255))), MWhite(CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
		HBRUSH W(CreateSolidBrush(RGB(255, 255, 255)));

		SelectPen(hDc, MWhite);
		SelectObject(hDc,MFont);

		double q(Rect.right/4);

		MoveToEx(hDc, Rect.left + xVe / 20, Rect.bottom/2, NULL);
		LineTo(hDc, Rect.right - xVe/ 20, Rect.bottom / 2);
		TextOut(hDc, Rect.right - xVe / 20, Rect.bottom / 2-yVe/50, "x", 1);

		MoveToEx(hDc, Rect.right/2, Rect.top+yVe/20, NULL);
		LineTo(hDc, Rect.right/2, Rect.bottom -yVe/ 20);
		TextOut(hDc, Rect.right/2+5, Rect.top +yVe/50, "y", 1);

		TextOut(hDc, Rect.right / 2-10, Rect.bottom/2-yVe/50, "0", 1);

		SetMapMode(hDc, MM_ANISOTROPIC);
		SetWindowExtEx(hDc, xVe, yVe, NULL);
		SetViewportExtEx(hDc, xVe, -yVe, NULL);
		SetViewportOrgEx(hDc, xVe / 2, yVe / 2, NULL);

		SelectPen(hDc, PWhite);

		double a(0), y(0), b(0);
		if (fFunc)
		{
			a = -20 * StepX;
			b = 20 * StepX;
			MoveToEx(hDc, a, F1(a), NULL);
			LineTo(hDc, b, F1(b));
		}
		if (sFunc)
		{
			a = -3.5 * StepX;
			b = 3.5 * StepX;
			MoveToEx(hDc, a, F2(a), NULL);
			for (double x(a); x <= b; x += 0.1)
				LineTo(hDc, x, F2(x));
		}
		if (tFunc)
		{
			a = StepX;
			b = 50 * StepX;
			MoveToEx(hDc, a, F3(a), NULL);
			for (double x(a); x <= b; x += 1)
				LineTo(hDc, x, F3(x));
		}

		if (Click) {

				string s("("), ss;
				double x((Point.x-xVe/2) / StepX);
				s += to_string(x);
				s += ", ";
				if (fFunc)
					s += to_string(F1(x));
				else
					if (sFunc)
						s += to_string(F2(x));
					else
						if (tFunc)
							s += to_string(F3(x));
				s += ")";
				char cStr[100];
				strcpy(cStr, s.c_str());
				TextOut(hDc, q, 60, cStr, strlen(cStr));
		}

		DeleteObject(PWhite);
		DeleteObject(MWhite);
		DeleteObject(MFont);

		EndPaint(hwnd, &PS);

		break;
	}
	case WM_CLOSE:
	{
		if (IDYES == MessageBox(hWnd, "Желаете закрыть приложение?", "Запрос о закрытии", MB_YESNO | MB_ICONQUESTION))
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
	WC.lpszClassName = "Лабораторная работа WinApi №4";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, "Ошибка регистрации оконного класса", "Ошибка WinApi. Лаба №4", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, "Лабораторная работа WinApi №4", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, "Ошибка создания главного окна", "Ошибка WinApi. Лаба №4", MB_OK);
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