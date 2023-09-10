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
static int t(0);
static bool actYellow(false), actRed(true), actGreen(false);

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
		if (t % 3 == 0 && actRed)
		{
			t = 0;
			actRed = false;
			actYellow = true;
			actGreen = false;
		}
		else 
			if (t % 3 == 0 && actYellow)
			{
				t = 0;
				actRed = false;
				actYellow = false;
				actGreen = true;
			}
		    else 
				if (t % 3 == 0 && actGreen)
				{
					t = 0;
					actRed = true;
					actYellow = false;
					actGreen = false;
				}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HBRUSH BARed(CreateSolidBrush(RGB(255,0,0)));
		HBRUSH BPRed(CreateSolidBrush(RGB(55, 0, 0)));

		HBRUSH BAYellow(CreateSolidBrush(RGB(255, 255, 0)));
		HBRUSH BPYellow(CreateSolidBrush(RGB(55, 55, 0)));

		HBRUSH BAGreen(CreateSolidBrush(RGB(0, 255, 0)));
		HBRUSH BPGreen(CreateSolidBrush(RGB(0, 55, 0)));

		HBRUSH BCBlack(CreateSolidBrush(RGB(0, 0, 0)));
		HPEN PCWhite(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));


		SelectObject(hDc, PCWhite);
		SelectObject(hDc, BCBlack);
		
		int Width(Rect.right/7),Height(Rect.right / 7*3);

		POINT Basic[4];
		Basic[0].x = Rect.right / 2 - Width/2;
		Basic[0].y = Rect.bottom / 2 + Height / 2;
		Basic[1].x = Rect.right / 2 - Width / 2;
		Basic[1].y = Rect.bottom / 2 - Height / 2;
		Basic[2].x = Rect.right / 2 + Width / 2;
		Basic[2].y = Rect.bottom / 2 - Height / 2;
		Basic[3].x = Rect.right / 2 + Width / 2;
		Basic[3].y = Rect.bottom / 2 + Height / 2;
		Polygon(hDc, Basic, 4);

		if (actRed)
		{
			SelectObject(hDc, BARed);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 -Height / 2 + 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 - Height / 2 +Width-10);
		}
		else
		{
			SelectObject(hDc, BPRed);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 - Height / 2 + 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 - Height / 2 + Width - 10);
		}

		if (actYellow)
		{
			SelectObject(hDc, BAYellow);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 - Width / 2 + 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 + Width/2 - 10);
		}
		else
		{
			SelectObject(hDc, BPYellow);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 - Width / 2 + 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 + Width / 2 - 10);
		}

		if (actGreen)
		{
			SelectObject(hDc, BAGreen);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 + Height / 2 - 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 + Height / 2 - Width + 10);
		}
		else
		{
			SelectObject(hDc, BPGreen);
			Ellipse(hDc, Rect.right / 2 - Width / 2 + 10, Rect.bottom / 2 + Height / 2 - 10, Rect.right / 2 + Width / 2 - 10, Rect.bottom / 2 + Height / 2 - Width + 10);
		}

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

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