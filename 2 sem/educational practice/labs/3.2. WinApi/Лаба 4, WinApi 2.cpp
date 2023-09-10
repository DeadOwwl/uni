#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "framework.h"
#include "cstring"
#include "string"

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

		HBRUSH BBlack(CreateSolidBrush(RGB(0, 0, 0)));
		HBRUSH BWhite(CreateSolidBrush(RGB(255, 255, 255)));

		int  Height(Rect.bottom - Rect.top), Width(Rect.right - Rect.left), sx(0), sy(0); 
		(Width > Height) ? sx = (Width - Height) / 2, Width = Height : sy = (Height - Width) / 2, Height = Width;
		int chHeight(Height / 10), chWidth(Width / 10);

		SelectObject(hDc, CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
		Rectangle(hDc, sx+ chWidth, sy+ chHeight, sx + 9 * chWidth, sy + 9 * chHeight);

		for (unsigned i(0); i < 8; i++)
			for (unsigned j(0); j < 8; j++) 
			{ 
				SelectObject(hDc, ((i ^ j) & 1) ? BBlack : BWhite);
				int x(sx + (i + 1) * chWidth), y(sy + (j + 1) * chHeight);
				Rectangle(hDc, x, y, x + chWidth, y + chHeight);
			} 

		RECT RC;
		wchar_t letter('a'), num('1');
		for (unsigned i(0); i < 8; i++)
		{
			RC.left = sx + (i + 1) * chWidth;
			RC.right = RC.left + chWidth;
			RC.top = sy + 9 * chHeight;
			RC.bottom = RC.top + chHeight;
			DrawText(hDc, &letter, 1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			letter++;

			RC.left = sx;
			RC.right = RC.left + chWidth;
			RC.top = sy + (8 - i) * chHeight;
			RC.bottom = RC.top + chHeight;
			DrawText(hDc, &num, 1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			num++;
		}

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		DeleteObject(BWhite);
		DeleteObject(BBlack);
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

	return (int )msg.wParam;
}