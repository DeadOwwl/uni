#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"
#include "ctime"

HWND hwnd;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
int sround(time(NULL));
int flag(0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	RECT Rect;
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

		HPEN PUniversal = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		HBRUSH BYellow = CreateSolidBrush(RGB(255, 215, 0)); //1
		HBRUSH BGreen = CreateSolidBrush(RGB(0, 255, 0)); //2
		HBRUSH BPurple = CreateSolidBrush(RGB(75, 0, 130)); //3
		HBRUSH BOrange = CreateSolidBrush(RGB(255, 69, 0)); //4
		HBRUSH BAquamarin = CreateSolidBrush(RGB(127, 255, 212)); //5
		HBRUSH BRed = CreateSolidBrush(RGB(139, 0, 0)); //6
		HBRUSH BBlue = CreateSolidBrush(RGB(25, 25, 112)); //7

		TextOut(hDc, Rect.right / 2 - 80, Rect.bottom / 2 - 100, L"Вариант №6 Крагель А. О.", 25);

		POINT Triangle[3];
		POINT Parallelogram[4];

		int vCenter((Rect.bottom - Rect.top) / 2), hCenter((Rect.right - Rect.left) / 2);

		SelectObject(hDc, PUniversal);

		//5
		SelectObject(hDc, BAquamarin);
		Triangle[0].x = hCenter + 100;
		Triangle[0].y = vCenter-80;
		Triangle[1].x = hCenter + 50;
		Triangle[1].y = vCenter-80;
		Triangle[2].x = hCenter + 75;
		Triangle[2].y = vCenter -55;
		Polygon(hDc, Triangle, 3);

		//7
		SelectObject(hDc, BBlue);
		Triangle[0].x = hCenter + 50;
		Triangle[0].y = vCenter - 80;
		Triangle[1].x = hCenter + 50;
		Triangle[1].y = vCenter - 30;
		Triangle[2].x = hCenter + 75;
		Triangle[2].y = vCenter - 55;
		Polygon(hDc, Triangle, 3);

		//3
		SelectObject(hDc, BPurple);
		Parallelogram[0].x = hCenter + 50;
		Parallelogram[0].y = vCenter - 30;
		Parallelogram[1].x = hCenter + 50;
		Parallelogram[1].y = vCenter + 20;
		Parallelogram[2].x = hCenter + 75;
		Parallelogram[2].y = vCenter - 5;
		Parallelogram[3].x = hCenter + 75;
		Parallelogram[3].y = vCenter - 55;
		Polygon(hDc, Parallelogram, 4);

		//1
		SelectObject(hDc, BYellow);
		Triangle[0].x = hCenter + 50;
		Triangle[0].y = vCenter - 10;
		Triangle[1].x = hCenter + 50;
		Triangle[1].y = vCenter + 110;
		Triangle[2].x = hCenter - 10;
		Triangle[2].y = vCenter + 50;
		Polygon(hDc, Triangle, 3);

		//6
		SelectObject(hDc, BRed);
		Parallelogram[0].x = hCenter + 50;
		Parallelogram[0].y = vCenter - 10;
		Parallelogram[1].x = hCenter+25;
		Parallelogram[1].y = vCenter - 35;
		Parallelogram[2].x = hCenter;
		Parallelogram[2].y = vCenter - 10;
		Parallelogram[3].x = hCenter+25;
		Parallelogram[3].y = vCenter + 15;
		Polygon(hDc, Parallelogram, 4);

		//4
		SelectObject(hDc, BOrange);
		Triangle[0].x = hCenter + 25;
		Triangle[0].y = vCenter + 15;
		Triangle[1].x = hCenter - 20;
		Triangle[1].y = vCenter - 30;
		Triangle[2].x = hCenter - 65;
		Triangle[2].y = vCenter + 15;
		Polygon(hDc, Triangle, 3);

		//2
		SelectObject(hDc, BGreen);
		Triangle[0].x = hCenter + 25;
		Triangle[0].y = vCenter + 15;
		Triangle[1].x = hCenter - 65;
		Triangle[1].y = vCenter + 15;
		Triangle[2].x = hCenter - 65;
		Triangle[2].y = vCenter + 105;
		Polygon(hDc, Triangle, 3);


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

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}