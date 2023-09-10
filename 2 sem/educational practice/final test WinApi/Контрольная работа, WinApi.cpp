#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define TIMER_SEC 1
#undef UNICODE
#define FILE_MENU_ABOUT 1
#define FILE_MENU_SHOW 2

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"
#include "cmath"
#include<iostream>
#include <CommCtrl.h>
#include <WinUser.h>
#include <WinGDI.h>

HWND hwnd;
RECT Rect;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
HMENU hMenu;
HWND hDiag1;
static bool go(false), show(false);
static int t(0), tDiag(0), flag(0);

LRESULT CALLBACK DiagProc(HWND hWnd, UINT  uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PS;
	RECT RECT;
	GetClientRect(hWnd, &RECT);
	HDC hDc;

	switch (uMsg)
	{
	case WM_PAINT:
	{
		hDc = BeginPaint(hWnd, &PS);
		SetTextColor(hDc, RGB(255, 255, 255));
		SetBkMode(hDc, TRANSPARENT);
		TextOut(hDc, RECT.left+10, RECT.top+10, "Алина Крагель, 1 курс, 10 группа, 30.04.2020", 45);
		EndPaint(hWnd, &PS);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		break;
	}
	return EXIT_SUCCESS;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT  uMsg, WPARAM wParam, LPARAM lParam)
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
		hMenu = CreateMenu();
		HMENU hFileMenu = CreateMenu();
		AppendMenu(hMenu, MF_STRING, FILE_MENU_ABOUT, "About");
		AppendMenu(hMenu, MF_STRING, FILE_MENU_SHOW, "Show");
		SetMenu(hWnd, hMenu);

		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
		break;
	}
	case WM_TIMER:
	{
		if (go && show && flag==1)
		{
			double lTg(Rect.right / Rect.bottom);
			t += 2;
			tDiag += 1 / lTg;
		}
		if (t + 400 >= Rect.right)
		{
			go = false;
			show = false;
			flag = 0;
			t = 0;
			tDiag = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HBRUSH shipPen(CreateSolidBrush(RGB(0, 255, 255)));
		HPEN shipBrush(CreatePen(PS_SOLID, 1, RGB(0, 255, 255)));

		POINT shipPart[4];

		SelectObject(hDc, shipPen);
		SelectObject(hDc, shipBrush);

			if (go && show)
			{
				//борт
				shipPart[0].x = Rect.right - 300 - t;
				shipPart[0].y = Rect.bottom - 100 - tDiag;

				shipPart[1].x = Rect.right - 400 - t;
				shipPart[1].y = Rect.bottom - 200 - tDiag;

				shipPart[2].x = Rect.right - t;
				shipPart[2].y = Rect.bottom - 200 - tDiag;

				shipPart[3].x = Rect.right - 100 - t;
				shipPart[3].y = Rect.bottom - 100 - tDiag;

				Polygon(hDc, shipPart, 4);

				//левый парус
				shipPart[0].x = Rect.right - 350 - t;
				shipPart[0].y = Rect.bottom - 220 - tDiag;

				shipPart[1].x = Rect.right - 200 - t;
				shipPart[1].y = Rect.bottom - 400 - tDiag;

				shipPart[2].x = Rect.right - 200 - t;
				shipPart[2].y = Rect.bottom - 220 - tDiag;

				Polygon(hDc, shipPart, 3);
				//правый парус
				shipPart[0].x = Rect.right - 20 - t;
				shipPart[0].y = Rect.bottom - 220 - tDiag;

				shipPart[1].x = Rect.right - 180 - t;
				shipPart[1].y = Rect.bottom - 400 - tDiag;

				shipPart[2].x = Rect.right - 180 - t;
				shipPart[2].y = Rect.bottom - 220 - tDiag;
				Polygon(hDc, shipPart, 3);
			}
			else
			{
				if (!go && show)
				{
					//борт
					shipPart[0].x = Rect.right - 300 - t;
					shipPart[0].y = Rect.bottom - 100 - tDiag;

					shipPart[1].x = Rect.right - 400 - t;
					shipPart[1].y = Rect.bottom - 200 - tDiag;

					shipPart[2].x = Rect.right - t;
					shipPart[2].y = Rect.bottom - 200 - tDiag;

					shipPart[3].x = Rect.right - 100 - t;
					shipPart[3].y = Rect.bottom - 100 - tDiag;

					Polygon(hDc, shipPart, 4);

					//левый парус
					shipPart[0].x = Rect.right - 350 - t;
					shipPart[0].y = Rect.bottom - 220 - tDiag;

					shipPart[1].x = Rect.right - 200 - t;
					shipPart[1].y = Rect.bottom - 400 - tDiag;

					shipPart[2].x = Rect.right - 200 - t;
					shipPart[2].y = Rect.bottom - 220 - tDiag;

					Polygon(hDc, shipPart, 3);
					//правый парус
					shipPart[0].x = Rect.right - 20 - t;
					shipPart[0].y = Rect.bottom - 220 - tDiag;

					shipPart[1].x = Rect.right - 180 - t;
					shipPart[1].y = Rect.bottom - 400 - tDiag;

					shipPart[2].x = Rect.right - 180 - t;
					shipPart[2].y = Rect.bottom - 220 - tDiag;
					Polygon(hDc, shipPart, 3);
				}
				else
				if (show && flag==1)
				{
					//борт
					shipPart[0].x = Rect.right - 300;
					shipPart[0].y = Rect.bottom - 100;

					shipPart[1].x = Rect.right - 400;
					shipPart[1].y = Rect.bottom - 200;

					shipPart[2].x = Rect.right;
					shipPart[2].y = Rect.bottom - 200;

					shipPart[3].x = Rect.right - 100;
					shipPart[3].y = Rect.bottom - 100;

					Polygon(hDc, shipPart, 4);

					//левый парус
					shipPart[0].x = Rect.right - 350;
					shipPart[0].y = Rect.bottom - 220;

					shipPart[1].x = Rect.right - 200;
					shipPart[1].y = Rect.bottom - 400;

					shipPart[2].x = Rect.right - 200;
					shipPart[2].y = Rect.bottom - 220;

					Polygon(hDc, shipPart, 3);
					//правый парус
					shipPart[0].x = Rect.right - 20;
					shipPart[0].y = Rect.bottom - 220;

					shipPart[1].x = Rect.right - 180;
					shipPart[1].y = Rect.bottom - 400;

					shipPart[2].x = Rect.right - 180;
					shipPart[2].y = Rect.bottom - 220;
					Polygon(hDc, shipPart, 3);
				}
			}


		DeleteObject(shipPen);
		DeleteObject(shipBrush);

		EndPaint(hwnd, &PS);

		break;
	}
	case WM_COMMAND:
	{

		switch (wParam)
		{
		case FILE_MENU_ABOUT:
		{
			hDiag1 = CreateWindow("MyDialogClass", "Об авторе", WS_VISIBLE | WS_OVERLAPPED | WS_POPUP | WS_CAPTION | WS_BORDER | WS_SYSMENU, 300, 200, 500, 300, hWnd, NULL, NULL, NULL);
			break;
		}
		case FILE_MENU_SHOW:
		{
			flag = 1;
			show = true;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}

		switch (LOWORD(wParam))
		{
		case 10000:
		{
			if (show)
			{
				SetTimer(hWnd, 1, 30, NULL);
				go = true;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case 10001:
		{
			go = false;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case 10002:
		{
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		}
	}

	EndPaint(hwnd, &PS);
	break;

	case WM_CLOSE:
	{
		if (IDYES == MessageBox(hWnd, "Желаете закрыть приложение?", "Запрос о закрытии", MB_YESNO | MB_ICONQUESTION))
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
	WC.lpszClassName = "Контрольная работа";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, "Ошибка регистрации оконного класса", "Ошибка", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, "Контрольная работа", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, "Ошибка создания главного окна", "Ошибка", MB_OK);
		return EXIT_FAILURE;
	}

	WNDCLASS dialog = { 0 };
	dialog.lpszClassName = "MyDialogClass";
	dialog.hInstance = hInstance;
	dialog.lpfnWndProc = DiagProc;
	dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	dialog.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0)));
	RegisterClass(&dialog);
	CreateWindow("BUTTON", "RUN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 5, 100, 20, hwnd, (HMENU)10000, hInstance, NULL);
	CreateWindow("BUTTON", "STOP", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 105, 5, 100, 20, hwnd, (HMENU)10001, hInstance, NULL);
	CreateWindow("BUTTON", "EXIT", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205, 5, 100, 20, hwnd, (HMENU)10002, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}