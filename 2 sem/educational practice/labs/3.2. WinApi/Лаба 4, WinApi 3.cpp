#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"

HWND hwnd;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
RECT Rect;
int sround(time(NULL));
int flag(0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	PAINTSTRUCT PS;

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
		GetClientRect(hwnd, &Rect);

		if (flag == 0)
			for (unsigned i(800); i > 0; i = i - 20)
			{
				HBRUSH HB(CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
				SelectObject(hDc, HB);
				Ellipse(hDc, Rect.right / 2 - i, Rect.bottom / 2 - i, Rect.right / 2 + i, Rect.bottom / 2 + i);
				DeleteObject(HB);
				DeleteObject(HB);
			}
		else {
			if (flag == 99)
				for (unsigned i(800); i > 0; i = i - 20)
				{
					HBRUSH HB(CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
					SelectObject(hDc, HB);
					Ellipse(hDc, Rect.right / 2 - i, Rect.bottom / 2 - i, Rect.right / 2 + i, Rect.bottom / 2 + i);
					DeleteObject(HB);
				}
			if (flag == 999)
				for (unsigned i(800), mColor(0); i > 0; i = i - 20, mColor+=4) {
					HBRUSH HB = CreateSolidBrush(RGB(mColor, mColor, mColor));
					HPEN HP = CreatePen(PS_NULL, 0, RGB(mColor, mColor, mColor));
					SelectObject(hDc, HB);
					SelectObject(hDc, HP);
					Ellipse(hDc, Rect.right / 2 - i, Rect.bottom / 2 - i, Rect.right / 2 + i, Rect.bottom / 2 + i);
					DeleteObject(HB);
					DeleteObject(HP);
				}
		}

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		//EndPaint(hwnd, &PS);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 99:
		{
			flag = 99;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case 999:
			flag = 999;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
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
	WC.lpszClassName = L"Лабораторная работа WinApi №2";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба №2", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, L"Лабораторная работа WinApi №2", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"Ошибка создания главного окна", L"Ошибка WinApi. Лаба №2", MB_OK);
		return EXIT_FAILURE;
	}

	CreateWindowW(L"BUTTON", L"Закрашиваем!", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 10, 100, 20, hwnd, (HMENU)99, hInstance, NULL);
	CreateWindowW(L"BUTTON", L"Обновляем!", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 410, 10, 100, 20, hwnd, (HMENU)999, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}