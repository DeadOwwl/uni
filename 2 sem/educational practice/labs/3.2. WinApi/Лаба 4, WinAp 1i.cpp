#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "framework.h"
#include "cstring"

HWND hwnd;
WNDCLASSEX WC{ sizeof(WNDCLASSEX) };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	RECT Rect;
	PAINTSTRUCT PS;

	switch (uMsg)
	{
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

		SelectObject(hDc, GetStockObject(WHITE_PEN));
		MoveToEx(hDc, Rect.left+20, Rect.top + 50, NULL);
		LineTo(hDc, Rect.right - 25, Rect.top + 50);
		MoveToEx(hDc, Rect.right-25, Rect.top + 50, NULL);
		LineTo(hDc, Rect.right - 25, Rect.bottom - 50);
		MoveToEx(hDc, Rect.right-25, Rect.bottom - 50, NULL);
		LineTo(hDc, Rect.left+20, Rect.bottom - 50);
		MoveToEx(hDc, Rect.left+20, Rect.bottom - 50, NULL);
		LineTo(hDc, Rect.left+20, Rect.top + 50);
		MoveToEx(hDc, Rect.left + 20, Rect.bottom/2, NULL);
		LineTo(hDc, Rect.right - 25, Rect.bottom/2);
		MoveToEx(hDc, Rect.right / 3 , Rect.bottom -50, NULL);
		LineTo(hDc, Rect.right / 3 , Rect.top +50);
		MoveToEx(hDc, Rect.right * 2 / 3 , Rect.bottom - 50, NULL);
		LineTo(hDc, Rect.right * 2 / 3 , Rect.top + 50);

		MoveToEx(hDc, Rect.left +40, Rect.bottom/2 -30, NULL);
		LineTo(hDc, Rect.right/3 -20, Rect.bottom / 2 - 30);
		MoveToEx(hDc, Rect.right / 3 - 20, Rect.bottom / 2 - 30, NULL);
		LineTo(hDc, Rect.right / 3/2 , Rect.bottom / 2 - ((Rect.right / 3 - 20)-(Rect.left + 40)));
		MoveToEx(hDc, Rect.right / 3 / 2, Rect.bottom / 2 - ((Rect.right / 3 - 20) - (Rect.left + 40)), NULL);
		LineTo(hDc, Rect.left + 40, Rect.bottom / 2 - 30);
		TextOut(hDc, Rect.left + 40, Rect.bottom / 2 - 20, L"Равносторонний треугольник", 27);
		
		SelectObject(hDc, CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
        Rectangle(hDc, Rect.right / 3 + 10, Rect.top + 80, Rect.right * 2 / 3 - 10, Rect.bottom / 2 -30);
		RECT R;
		R.bottom = Rect.bottom / 2 - 31;
		R.top = Rect.top + 80;
		R.right = Rect.right * 2 / 3 - 11;
		R.left = Rect.right / 3 + 10;
		FillRect(hDc, &R, CreateSolidBrush(RGB(0, 0, 0)));
		TextOut(hDc, Rect.right / 3 + 80, Rect.bottom / 2 - 20, L"Прямоугольник", 14);

		SelectObject(hDc, CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
		Rectangle(hDc, Rect.right * 2 / 3 + 35, Rect.top + 85, Rect.right - 60, Rect.bottom / 2 - 30);
		R.bottom = Rect.bottom / 2 - 31;
		R.top = Rect.top + 85;
		R.right = Rect.right - 61;
		R.left = Rect.right * 2 / 3 + 35;
		FillRect(hDc, &R, CreateSolidBrush(RGB(0, 0, 0)));
		TextOut(hDc, Rect.right * 2 / 3 + 90, Rect.bottom / 2 - 20, L"Квадрат", 8);

		SelectObject(hDc, GetStockObject(WHITE_PEN));
		MoveToEx(hDc, Rect.left + 60, Rect.bottom / 2 + 120, NULL);
		LineTo(hDc, Rect.right / 3 /2, Rect.bottom / 2 + 30);
		MoveToEx(hDc, Rect.right / 3 / 2, Rect.bottom / 2 + 30, NULL);
		LineTo(hDc, Rect.right / 3 - 60, Rect.bottom / 2 + 120);
		MoveToEx(hDc, Rect.right / 3 - 60, Rect.bottom / 2 + 120, NULL);
		LineTo(hDc, Rect.right / 3 / 2, Rect.bottom - 65);
		MoveToEx(hDc, Rect.left + 60, Rect.bottom / 2 + 120, NULL);
		LineTo(hDc, Rect.right / 3 / 2, Rect.bottom - 65);
		TextOut(hDc, Rect.left + 115, Rect.bottom - 70, L"Ромб", 4);

		SelectObject(hDc, GetStockObject(BLACK_BRUSH));
		Ellipse(hDc, Rect.right / 3 + 10, Rect.bottom / 2 + 30, Rect.right * 2 / 3 - 10, Rect.bottom - 80);
		TextOut(hDc, Rect.right/3 + 110, Rect.bottom - 70, L"Эллипс", 7);

		Pie(hDc, Rect.right * 2 / 3 + 35, Rect.bottom / 2 + 30, Rect.right - 60, Rect.bottom - 80, Rect.right -25, Rect.bottom - 165, Rect.right*2/3 + 25, Rect.bottom - 165);
		TextOut(hDc, Rect.right*2 / 3 + 70, Rect.bottom - 70, L"Сектор (180 гр.)", 17);
		
		DrawText(hDc, L"Крагель А. О.", 14, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		EndPaint(hwnd, &PS);
		break;
	}
	case WM_MOUSEMOVE:
	{
		int a(LOWORD(lParam)), b(HIWORD(lParam));
		RECT nRect;
		int f(0);
		GetClientRect(hwnd, &nRect);
		double xC(nRect.right / 3), yC(nRect.bottom / 2);
		if ((a <= xC) && (b <= yC) && (a >= 0) && (b >= 0) && (f != 1)) {
			f = 1;
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		if ((a <= 2 * xC) && (b <= yC) && (a >= xC) && (b >= 0) && (f != 2)) {
			f = 2;
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		if ((a <= 3 * xC) && (b <= yC) && (a >= 2 * xC) && (b >= 0) && (f != 3)) {
			f = 3;
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		if ((a <= xC) && (b < 2 * yC) && (a >= 0) && (b >= yC) && (f != 4)) {
			f = 4;
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		if ((a < 2*xC) && (b <= 2 * yC) && (a >= xC) && (b >= yC) && (f != 5)) {
			f = 5;
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		if ((a < 3*xC) && (b <= 2 * yC) && (a >= 2 * xC) && (b >= yC) && (f != 6)) {
			f = 6;
			SetCursor(LoadCursor(NULL, IDC_NO));
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
	WC.hbrBackground = (HBRUSH)(BLACK_BRUSH);
	WC.lpszMenuName = NULL;
	WC.lpszClassName = L"Лабораторная работа WinApi №2";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба №2", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, L"Лабораторная работа WinApi №2", WS_OVERLAPPEDWINDOW | WS_BORDER | WS_VISIBLE,
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

	return msg.wParam;
}