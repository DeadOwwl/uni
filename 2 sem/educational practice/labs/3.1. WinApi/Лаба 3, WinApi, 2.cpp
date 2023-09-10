#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "Лаба 3, WinApi.h"
#include "Windows.h"
#include "cstring"

HWND hwnd;

//Оконная процедура-рисовашка
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	RECT Rect;
	PAINTSTRUCT PS;
	int userReply;
	HBRUSH BRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH BGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH BBlue = CreateSolidBrush(RGB(0, 0, 255));
	HPEN PRed = CreatePen(PS_SOLID, 3, RGB(128, 0, 0));
	HPEN PGreen = CreatePen(PS_SOLID, 3, RGB(0, 150, 0));
	HPEN PBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 150));
	switch (uMsg)
	{
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_PAINT:
	{
		hDC = BeginPaint(hwnd, &PS);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		GetClientRect(hwnd, &Rect);

		SelectObject(hDC, PRed);
		SelectObject(hDC, BRed);
		Rectangle(hDC, Rect.left + 20, Rect.top + 20, Rect.right - 20, Rect.bottom - 20);

		SelectObject(hDC, PBlue);
		SelectObject(hDC, BBlue);
		Ellipse(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);

		SelectObject(hDC, PRed);
		SelectObject(hDC, BRed);
		Ellipse(hDC, Rect.left + 20, Rect.top + 20, Rect.right - 20, Rect.bottom - 20);

		SelectObject(hDC, PGreen);
		SelectObject(hDC, BGreen);
		ExtFloodFill(hDC, Rect.right / 2, Rect.bottom / 2, RGB(128, 0, 0), FLOODFILLBORDER);
		
		SelectObject(hDC, GetStockObject(WHITE_PEN));
		MoveToEx(hDC, Rect.left, Rect.top, NULL);
		LineTo(hDC, Rect.right, Rect.bottom);

		MoveToEx(hDC, Rect.right, Rect.top, NULL);
		LineTo(hDC, Rect.left, Rect.bottom);

		DrawText(hDC, L"Левый верхний угол", 19, &Rect, DT_SINGLELINE | DT_TOP | DT_LEFT);
		DrawText(hDC, L"Правый верхний угол", 20, &Rect, DT_SINGLELINE | DT_TOP | DT_RIGHT);
		DrawText(hDC, L"Правый нижний угол", 19, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
		DrawText(hDC, L"Левый нижний угол", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_LEFT);
		DrawText(hDC, L"КРАГЕЛЬ", 8, &Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		EndPaint(hwnd, &PS);
		break;
	}
	case WM_CLOSE:
	{
		userReply = MessageBox(hWnd, L"Желаете закрыть приложение?", L"Запрос о закрытии", MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
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
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lCmdShow, int nCmdShow) 
{
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };
MSG msg;
WC.style = CS_VREDRAW | CS_HREDRAW;
WC.cbClsExtra = 0;
WC.cbWndExtra = 0;
WC.hInstance = hInstance;
WC.hIcon = LoadIcon(NULL, IDI_ASTERISK);
WC.hCursor = LoadCursor(NULL, IDC_ARROW);
WC.hbrBackground = (HBRUSH)(COLOR_WINDOW);
WC.lpszMenuName = NULL;
WC.lpszClassName = L"Лабораторная работа WinApi №1" ;
WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);

WC.lpfnWndProc = WndProc;

//Регистрируем класс окна
if (!RegisterClassEx(&WC)) 
{
	MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба #1", MB_OK);
	return EXIT_FAILURE;
}

//Создаем основное окно приложения
hwnd = CreateWindow(
	WC.lpszClassName, L"Лабораторная работа WinApi №1", WS_OVERLAPPEDWINDOW | WS_BORDER | WS_VISIBLE,
	CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, WC.hInstance, NULL);

if (!hwnd) 
{
	MessageBox(NULL, L"Ошибка создания главного окна", L"Ошибка WinApi. Лаба #1", MB_OK);
	return EXIT_FAILURE;
}

//Показываю окно
ShowWindow(hwnd, nCmdShow);

//Выполнение цикла обработки сообщений до закрытия приложения
while (GetMessage(&msg, NULL, 0, 0))
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

return msg.wParam;
};