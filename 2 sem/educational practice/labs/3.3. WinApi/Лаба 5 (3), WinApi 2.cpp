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
static int t(0), m(0);

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
		if (t == 60)
		{
			t = 0;
			m++;
		}
		if (m == 60)
			m = 0;
		InvalidateRect(hWnd, NULL, TRUE);
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		int W(Rect.bottom / 2), H(Rect.right / 2),L(0);
		if (W > H)
			L = H / 2;
		else
			L = W / 2;

		double trAngle(M_PI / 6), sxAngle(M_PI / 3);
		HPEN WPen(CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
		HPEN L1Pen(CreatePen(PS_SOLID, 4, RGB(255, 255, 255)));
		HBRUSH BBrush(CreateSolidBrush(RGB(0, 0, 0)));
		HFONT MFont(CreateFontW(30, 10, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, L"Gabriola"));

		SelectObject(hDc, MFont);
		SelectObject(hDc, WPen);
		SelectObject(hDc, BBrush);
		Rectangle(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 - H / 2, Rect.right / 2 + W / 2, Rect.bottom / 2 + H / 2);

		MoveToEx(hDc, Rect.right / 2, Rect.bottom / 2 - H / 2, NULL);
		LineTo(hDc, Rect.right / 2, Rect.bottom / 2 -  5*H /12 );
		TextOut(hDc, Rect.right / 2-10, Rect.bottom / 2 - 5 * H / 12 + 2, L"XII", 3);

		if ((H / 2 * tan(trAngle))<(W/2))
		{
			MoveToEx(hDc, Rect.right / 2 + H / 2 * tan(trAngle), Rect.bottom / 2 - H / 2, NULL);
			LineTo(hDc, Rect.right / 2 + H / 2 * tan(trAngle) - H / 12 * tan(trAngle), Rect.bottom / 2 - H / 2 + H / 12);
			TextOut(hDc, Rect.right / 2 + H / 2 * tan(trAngle) - H / 12 * tan(trAngle)-6, Rect.bottom / 2 - H / 2 + H / 12+5, L"I", 1);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 + W/2, Rect.bottom / 2 - W / 2*tan(sxAngle), NULL);
			LineTo(hDc, Rect.right / 2 + W / 2 - H / 12, Rect.bottom / 2 - W / 2 * tan(sxAngle) + H / 12 * tan(sxAngle));
			TextOut(hDc, Rect.right / 2 + W / 2 - H / 12-6, Rect.bottom / 2 - W / 2 * tan(sxAngle) + H / 12 * tan(sxAngle)+5, L"I", 1);
		}

		if ((W / 2 * tan(trAngle)) < (H / 2))
		{
			MoveToEx(hDc, Rect.right / 2 + W / 2, Rect.bottom / 2 - W/2*tan(trAngle), NULL);
			LineTo(hDc, Rect.right / 2 + W / 2 - H / 12, Rect.bottom / 2 - W / 2 * tan(trAngle) + H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 + W / 2 - H / 12 - 12, Rect.bottom / 2 - W / 2 * tan(trAngle) + H / 12 * tan(trAngle)-4, L"II", 2);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 + H / 2/tan(trAngle), Rect.bottom / 2 -H/2, NULL);
			LineTo(hDc, Rect.right / 2 + H / 2 / tan(trAngle) - H / 15, Rect.bottom / 2 - H / 2 + H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 + H / 2 / tan(trAngle) - H / 15, Rect.bottom / 2 - H / 2 + H / 12 * tan(trAngle), L"II", 2);
		}

		MoveToEx(hDc, Rect.right / 2+W/2, Rect.bottom / 2, NULL);
		LineTo(hDc, Rect.right / 2+W/2-H/12, Rect.bottom / 2);
		TextOut(hDc, Rect.right / 2 + W / 2 - H / 12 -15, Rect.bottom / 2-7, L"III", 3);

		if ((W / 2 * tan(trAngle)) < (H / 2))
		{
			MoveToEx(hDc, Rect.right / 2 + W / 2, Rect.bottom / 2 + W / 2 * tan(trAngle), NULL);
			LineTo(hDc, Rect.right / 2 + W / 2 - H / 12, Rect.bottom / 2 + W / 2 * tan(trAngle) - H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 + W / 2 - H / 12 - 15, Rect.bottom / 2 + W / 2 * tan(trAngle) - H / 12 * tan(trAngle)-7, L"IV", 2);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 + H / 2 / tan(trAngle), Rect.bottom / 2 + H / 2, NULL);
			LineTo(hDc, Rect.right / 2 + H / 2 / tan(trAngle) - H / 12, Rect.bottom / 2 + H / 2 - H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 + H / 2 / tan(trAngle) - H / 12-15, Rect.bottom / 2 + H / 2 - H / 12 * tan(trAngle)-7, L"IV", 2);
		}

		if ((H / 2 * tan(trAngle)) < (W / 2))
		{
			MoveToEx(hDc, Rect.right / 2 + H / 2 * tan(trAngle), Rect.bottom / 2 + H / 2, NULL);
			LineTo(hDc, Rect.right / 2 + H / 2 * tan(trAngle) - H / 12 * tan(trAngle), Rect.bottom / 2 + H / 2 - H / 12);
			TextOut(hDc, Rect.right / 2 + H / 2 * tan(trAngle) - H / 12 * tan(trAngle) - 10, Rect.bottom / 2 + H / 2 - H / 12 -20, L"V", 1);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 + W / 2, Rect.bottom / 2 + W / 2 * tan(sxAngle), NULL);
			LineTo(hDc, Rect.right / 2 + W / 2 - H / 12, Rect.bottom / 2 + W / 2 * tan(sxAngle) - H / 12 * tan(sxAngle));
			TextOut(hDc, Rect.right / 2 + W / 2 - H / 12 - 10, Rect.bottom / 2 + W / 2 * tan(sxAngle) - H / 12 * tan(sxAngle) - 20, L"V", 1);
		}

		MoveToEx(hDc, Rect.right / 2, Rect.bottom / 2 + H / 2, NULL);
		LineTo(hDc, Rect.right / 2, Rect.bottom / 2 + 5 * H / 12);
		TextOut(hDc, Rect.right / 2-5, Rect.bottom / 2 + 5 * H / 12-20, L"VI", 2);

		if ((H / 2 * tan(trAngle)) < (W / 2))
		{
			MoveToEx(hDc, Rect.right / 2 - H / 2 * tan(trAngle), Rect.bottom / 2 + H / 2, NULL);
			LineTo(hDc, Rect.right / 2 - H / 2 * tan(trAngle) + H / 12 * tan(trAngle), Rect.bottom / 2 + H / 2 - H / 12);
			TextOut(hDc, Rect.right / 2 - H / 2 * tan(trAngle) + H / 12 * tan(trAngle)+7, Rect.bottom / 2 + H / 2 - H / 12-20, L"VII", 3);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 + W / 2 * tan(sxAngle), NULL);
			LineTo(hDc, Rect.right / 2 - W / 2 + H / 12 , Rect.bottom / 2 + W / 2 * tan(sxAngle) - H / 12 * tan(sxAngle));
			TextOut(hDc, Rect.right / 2 - W / 2 + H / 12+7, Rect.bottom / 2 + W / 2 * tan(sxAngle) - H / 12 * tan(sxAngle)-20, L"VII", 3);
		}

		if ((W / 2 * tan(trAngle)) < (H / 2))
		{
			MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 + W / 2 * tan(trAngle), NULL);
			LineTo(hDc, Rect.right / 2 - W / 2 + H / 12, Rect.bottom / 2 + W / 2 * tan(trAngle) - H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 - W / 2 + H / 12 + 5, Rect.bottom / 2 + W / 2 * tan(trAngle) - H / 12 * tan(trAngle)-7, L"VIII", 4);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 - H / 2 / tan(trAngle), Rect.bottom / 2 + H / 2, NULL);
			LineTo(hDc, Rect.right / 2 - H / 2 / tan(trAngle) + H / 12, Rect.bottom / 2 + H / 2 - H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 - H / 2 / tan(trAngle) + H / 12+5, Rect.bottom / 2 + H / 2 - H / 12 * tan(trAngle)-7, L"VIII", 4);
		}

		MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2, NULL);
		LineTo(hDc, Rect.right / 2 - W / 2 + H / 12, Rect.bottom / 2);
		TextOut(hDc, Rect.right / 2 - W / 2 + H / 12+4, Rect.bottom / 2 - 7, L"IX", 2);

		if ((W / 2 * tan(trAngle)) < (H / 2))
		{
			MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 - W / 2 * tan(trAngle), NULL);
			LineTo(hDc, Rect.right / 2 - W / 2 + H / 12, Rect.bottom / 2 - W / 2 * tan(trAngle) + H / 12 * tan(trAngle));
			TextOut(hDc, Rect.right / 2 - W / 2 + H / 12 +4, Rect.bottom / 2 - W / 2 * tan(trAngle) + H / 12 * tan(trAngle), L"X", 1);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 - H / 2 / tan(trAngle), Rect.bottom / 2 - H / 2, NULL);
			LineTo(hDc, Rect.right / 2 - H / 2 / tan(trAngle) + H / 15, Rect.bottom / 2 - H / 2 + H / 12 * tan(trAngle));
		}

		if ((H / 2 * tan(trAngle)) < (W / 2))
		{
			MoveToEx(hDc, Rect.right / 2 - H / 2 * tan(trAngle), Rect.bottom / 2 - H / 2, NULL);
			LineTo(hDc, Rect.right / 2 - H / 2 * tan(trAngle) + H / 12 * tan(trAngle), Rect.bottom / 2 - H / 2 + H / 12);
			TextOut(hDc, Rect.right / 2 - H / 2 * tan(trAngle) + H / 12 * tan(trAngle) + 4, Rect.bottom / 2 - H / 2 + H / 12 + 5, L"XI", 2);
		}
		else
		{
			MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 - W / 2 * tan(sxAngle), NULL);
			LineTo(hDc, Rect.right / 2 - W / 2 + H / 12, Rect.bottom / 2 - W / 2 * tan(sxAngle) + H / 12 * tan(sxAngle));
			TextOut(hDc, Rect.right / 2 - W / 2 + H / 12 + 4, Rect.bottom / 2 - W / 2 * tan(sxAngle) + H / 12 * tan(sxAngle) + 5, L"XI", 2);
		}

		for (unsigned i(1); i < 15; i++)
		{
			if ((H / 2 * tan(i*6*M_PI/180)) < (W / 2))
			{
				MoveToEx(hDc, Rect.right / 2 + H / 2 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 - H / 2, NULL);
				LineTo(hDc, Rect.right / 2 + H / 2 * tan(i * 6 * M_PI / 180) - H / 50 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 - H / 2 + H / 50);

				MoveToEx(hDc, Rect.right / 2 + H / 2 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 + H / 2, NULL);
				LineTo(hDc, Rect.right / 2 + H / 2 * tan(i * 6 * M_PI / 180) - H / 50 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 + H / 2 - H / 50);
			
				MoveToEx(hDc, Rect.right / 2 - H / 2 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 - H / 2, NULL);
				LineTo(hDc, Rect.right / 2 - H / 2 * tan(i * 6 * M_PI / 180) + H / 50 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 - H / 2 + H / 50);

				MoveToEx(hDc, Rect.right / 2 - H / 2 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 + H / 2, NULL);
				LineTo(hDc, Rect.right / 2 - H / 2 * tan(i * 6 * M_PI / 180) + H / 50 * tan(i * 6 * M_PI / 180), Rect.bottom / 2 + H / 2 - H / 50);
			}
			else
			{
				MoveToEx(hDc, Rect.right / 2 + W / 2, Rect.bottom / 2 - W / 2 * tan(M_PI/2- i * 6 * M_PI / 180), NULL);
				LineTo(hDc, Rect.right / 2 + W / 2 - H / 50, Rect.bottom / 2 - W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180) + H / 50 * tan(M_PI/2- i * 6 * M_PI / 180));
			
				MoveToEx(hDc, Rect.right / 2 + W / 2, Rect.bottom / 2 + W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180), NULL);
				LineTo(hDc, Rect.right / 2 + W / 2 - H / 50, Rect.bottom / 2 + W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180) - H / 50 * tan(M_PI / 2 - i * 6 * M_PI / 180));

				MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 - W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180), NULL);
				LineTo(hDc, Rect.right / 2 - W / 2 + H / 50, Rect.bottom / 2 - W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180) + H / 50 * tan(M_PI / 2 - i * 6 * M_PI / 180));

				MoveToEx(hDc, Rect.right / 2 - W / 2, Rect.bottom / 2 + W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180), NULL);
				LineTo(hDc, Rect.right / 2 - W / 2 + H / 50, Rect.bottom / 2 + W / 2 * tan(M_PI / 2 - i * 6 * M_PI / 180) - H / 50 * tan(M_PI / 2 - i * 6 * M_PI / 180));

			}
		}

		SelectObject(hDc, L1Pen);
		MoveToEx(hDc, Rect.right / 2 + L / 2 * sin(t * M_PI / 30), Rect.bottom / 2 - L / 2 * cos(t * M_PI / 30), NULL);
		LineTo(hDc, Rect.right / 2, Rect.bottom / 2);

		SelectObject(hDc, WPen);
		MoveToEx(hDc, Rect.right / 2 + L *sin(m * M_PI / 30), Rect.bottom / 2 - L * cos(m * M_PI / 30), NULL);
		LineTo(hDc, Rect.right / 2, Rect.bottom / 2 );

		DrawText(hDc, L"made by dead.owwl", 18, &Rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		EndPaint(hwnd, &PS);

		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ADD:
		{
			SetTimer(hWnd, 1, 1000, NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_SUBTRACT:
		{
			KillTimer(hWnd, 1);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
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
	WC.lpszClassName = L"Лабораторная работа WinApi №3";
	WC.hIconSm = LoadIcon(NULL, IDI_ASTERISK);;

	WC.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&WC))
	{
		MessageBox(NULL, L"Ошибка регистрации оконного класса", L"Ошибка WinApi. Лаба №3", MB_OK);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindow(WC.lpszClassName, L"Лабораторная работа WinApi №3", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, WC.hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"Ошибка создания главного окна", L"Ошибка WinApi. Лаба №3", MB_OK);
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