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
static bool inRect(false), onDiag(false), anSide(false);
static int t(0), tDiag(0);

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
		SetTimer(hWnd, TIMER_SEC, 30, NULL);
		SetClassLong(hWnd, GCL_HBRBACKGROUND,
			(LONG)CreateSolidBrush(RGB(0, 0, 0)));
	}
	case WM_TIMER:
	{
		if (t <= Rect.right / 4 && !onDiag)
			t += 3;
		else 
			if (t <= Rect.right / 2 && !onDiag)
				t += 7;
			else 
				if (t <= Rect.right * 3 / 4 && !onDiag)
					t += 3;
				else
					if (!onDiag)
						t+=7;
					else 
						if (!anSide) 
						{
							double lTg(Rect.right / Rect.bottom);
							t += 2;
							tDiag +=1 / lTg;
						}
						else 
						{
							double lTg(Rect.right / Rect.bottom);
							t -= 2;
							tDiag -= 1 / lTg;
						}					

		if (t-400>= Rect.right && !onDiag) {
			t = 0;
			inRect = true;
		}

		if (t >= 435 && inRect)
			onDiag = true;

		if (Rect.bottom *3/4<= tDiag && inRect && onDiag)
			anSide = true;

		if (tDiag <= -265 && anSide) 
		{
			inRect = false;
			onDiag = false;
			anSide = false;
			t = 0;
			tDiag = 0;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	case WM_PAINT:
	{
		hDc = BeginPaint(hwnd, &PS);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));

		HBRUSH catPen(CreateSolidBrush(RGB(0, 255-t/5, 255-t/5)));
		HPEN catBrush(CreatePen(PS_SOLID, 1, RGB(0, 255-t/5, 255-t/5)));

		POINT catPart[4];
		SelectObject(hDc, catPen);
		SelectObject(hDc, catBrush);

		if (!anSide)
		{
			if (!onDiag)
			{
				if (!inRect)
				{
					//Туловище
					catPart[0].x = Rect. right+335 - t;//100
					catPart[0].y = Rect.bottom - 100;
					catPart[1].x = Rect.right+335 - t;
					catPart[1].y = Rect.bottom - 180;
					catPart[2].x = Rect.right +135 - t; //300
					catPart[2].y = Rect.bottom - 180;
					catPart[3].x = Rect.right+135- t;
					catPart[3].y = Rect.bottom - 100;
					Polygon(hDc, catPart, 4);

					//Ножка задняя
					catPart[0].x = Rect.right +335 - t;//100
					catPart[0].y = Rect.bottom - 50;
					catPart[1].x = Rect.right +335 - t;
					catPart[1].y = Rect.bottom - 100;
					catPart[2].x = Rect.right +285 - t;//150
					catPart[2].y = Rect.bottom - 100;
					catPart[3].x = Rect.right +285 - t;
					catPart[3].y = Rect.bottom - 50;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right +285 - t, Rect.bottom - 75, Rect.right+335 - t, Rect.bottom - 25);

					//Ножка передняя
					catPart[0].x = Rect.right+185 - t;//250
					catPart[0].y = Rect.bottom - 50;
					catPart[1].x = Rect.right +185 - t;
					catPart[1].y = Rect.bottom - 100;
					catPart[2].x = Rect.right +135 - t;//300
					catPart[2].y = Rect.bottom - 100;
					catPart[3].x = Rect.right +135 - t;
					catPart[3].y = Rect.bottom - 50;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right+135 - t, Rect.bottom - 75, Rect.right+185- t, Rect.bottom - 25);

					//Хвост
					catPart[0].x = Rect.right+335- t;//100
					catPart[0].y = Rect.bottom - 180;
					catPart[1].x = Rect.right+335 - t;
					catPart[1].y = Rect.bottom - 260;
					catPart[2].x = Rect.right +285- t;//150
					catPart[2].y = Rect.bottom - 260;
					catPart[3].x = Rect.right +285- t;
					catPart[3].y = Rect.bottom - 180;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right +285 - t, Rect.bottom - 285, Rect.right+335 - t, Rect.bottom - 235);

					//Голова
					catPart[0].x = Rect.right +65-t;//370
					catPart[0].y = Rect.bottom - 150;
					catPart[1].x = Rect.right +225-t;//210
					catPart[1].y = Rect.bottom - 210;
					catPart[2].x = Rect.right+185-t;//250
					catPart[2].y = Rect.bottom - 305;
					catPart[3].x = Rect.right +25-t;//410
					catPart[3].y = Rect.bottom - 245;
					Polygon(hDc, catPart, 4);			
					
					//Уши
					catPart[0].x = Rect.right+25 - t;//410
					catPart[0].y = Rect.bottom - 245;
					catPart[1].x = Rect.right +135 - t;//300
					catPart[1].y = Rect.bottom - 245;
					catPart[2].x = Rect.right - t;//435
					catPart[2].y = Rect.bottom - 305;
					Polygon(hDc, catPart, 3);

					catPart[0].x = Rect.right +185 - t;//250
					catPart[0].y = Rect.bottom - 305;
					catPart[1].x = Rect.right +110- t;//325
					catPart[1].y = Rect.bottom - 245;
					catPart[2].x = Rect.right +160- t;//275
					catPart[2].y = Rect.bottom - 365;
					Polygon(hDc, catPart, 3);

				}
				else
				{
					//Туловище
					catPart[0].x = Rect.right - 100 - t +435;
					catPart[0].y = Rect.bottom - 100;
					catPart[1].x = Rect.right - 100 - t + 435;
					catPart[1].y = Rect.bottom - 180;
					catPart[2].x = Rect.right - 300 - t + 435;
					catPart[2].y = Rect.bottom - 180;
					catPart[3].x = Rect.right - 300 - t + 435;
					catPart[3].y = Rect.bottom - 100;
					Polygon(hDc, catPart, 4);

					//Ножка задняя
					catPart[0].x = Rect.right - 100 - t + 435;
					catPart[0].y = Rect.bottom - 50;
					catPart[1].x = Rect.right - 100 - t + 435;
					catPart[1].y = Rect.bottom - 100;
					catPart[2].x = Rect.right - 150 - t + 435;
					catPart[2].y = Rect.bottom - 100;
					catPart[3].x = Rect.right - 150 - t + 435;
					catPart[3].y = Rect.bottom - 50;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right - 150 - t + 435, Rect.bottom - 75, Rect.right - 100 - t + 435, Rect.bottom - 25);

					//Ножка передняя
					catPart[0].x = Rect.right - 250 - t + 435;
					catPart[0].y = Rect.bottom - 50;
					catPart[1].x = Rect.right - 250 - t + 435;
					catPart[1].y = Rect.bottom - 100;
					catPart[2].x = Rect.right - 300 - t + 435;
					catPart[2].y = Rect.bottom - 100;
					catPart[3].x = Rect.right - 300 - t + 435;
					catPart[3].y = Rect.bottom - 50;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right - 300 - t + 435, Rect.bottom - 75, Rect.right - 250 - t + 435, Rect.bottom - 25);

					//Хвост
					catPart[0].x = Rect.right - 100 - t + 435;
					catPart[0].y = Rect.bottom - 180;
					catPart[1].x = Rect.right - 100 - t + 435;
					catPart[1].y = Rect.bottom - 260;
					catPart[2].x = Rect.right - 150 - t + 435;
					catPart[2].y = Rect.bottom - 260;
					catPart[3].x = Rect.right - 150 - t + 435;
					catPart[3].y = Rect.bottom - 180;
					Polygon(hDc, catPart, 4);
					Ellipse(hDc, Rect.right - 150 - t + 435, Rect.bottom - 285, Rect.right - 100 - t + 435, Rect.bottom - 235);

					//Голова
					catPart[0].x = Rect.right - 370 - t + 435;
					catPart[0].y = Rect.bottom - 150;
					catPart[1].x = Rect.right - 210 - t + 435;
					catPart[1].y = Rect.bottom - 210;
					catPart[2].x = Rect.right - 250 - t + 435;
					catPart[2].y = Rect.bottom - 305;
					catPart[3].x = Rect.right - 410 - t + 435;
					catPart[3].y = Rect.bottom - 245;
					Polygon(hDc, catPart, 4);

					//Уши
					catPart[0].x = Rect.right - 410 - t + 435;
					catPart[0].y = Rect.bottom - 245;
					catPart[1].x = Rect.right - 300 - t + 435;
					catPart[1].y = Rect.bottom - 245;
					catPart[2].x = Rect.right - 435 - t + 435;
					catPart[2].y = Rect.bottom - 305;
					Polygon(hDc, catPart, 3);

					catPart[0].x = Rect.right - 250 - t + 435;
					catPart[0].y = Rect.bottom - 305;
					catPart[1].x = Rect.right - 325 - t + 435;
					catPart[1].y = Rect.bottom - 245;
					catPart[2].x = Rect.right - 275 - t + 435;
					catPart[2].y = Rect.bottom - 365;
					Polygon(hDc, catPart, 3);
				}
			}
			else
			{
			//Туловище
			catPart[0].x = Rect.right - 100 - t + 435;
			catPart[0].y = Rect.bottom - 100-tDiag;
			catPart[1].x = Rect.right - 100 - t + 435;
			catPart[1].y = Rect.bottom - 180 - tDiag;
			catPart[2].x = Rect.right - 300 - t + 435;
			catPart[2].y = Rect.bottom - 180 - tDiag;
			catPart[3].x = Rect.right - 300 - t + 435;
			catPart[3].y = Rect.bottom - 100 - tDiag;
			Polygon(hDc, catPart, 4);

			//Ножка задняя
			catPart[0].x = Rect.right - 100 - t + 435;
			catPart[0].y = Rect.bottom - 50 - tDiag;
			catPart[1].x = Rect.right - 100 - t + 435;
			catPart[1].y = Rect.bottom - 100 - tDiag;
			catPart[2].x = Rect.right - 150 - t + 435;
			catPart[2].y = Rect.bottom - 100 - tDiag;
			catPart[3].x = Rect.right - 150 - t + 435;
			catPart[3].y = Rect.bottom - 50 - tDiag;
			Polygon(hDc, catPart, 4);
			Ellipse(hDc, Rect.right - 150 - t + 435, Rect.bottom - 75 - tDiag, Rect.right - 100 - t + 435, Rect.bottom - 25 - tDiag);

			//Ножка передняя
			catPart[0].x = Rect.right - 250 - t + 435;
			catPart[0].y = Rect.bottom - 50 - tDiag;
			catPart[1].x = Rect.right - 250 - t + 435;
			catPart[1].y = Rect.bottom - 100 - tDiag;
			catPart[2].x = Rect.right - 300 - t + 435;
			catPart[2].y = Rect.bottom - 100 - tDiag;
			catPart[3].x = Rect.right - 300 - t + 435;
			catPart[3].y = Rect.bottom - 50 - tDiag;
			Polygon(hDc, catPart, 4);
			Ellipse(hDc, Rect.right - 300 - t + 435, Rect.bottom - 75 - tDiag, Rect.right - 250 - t + 435, Rect.bottom - 25 - tDiag);

			//Хвост
			catPart[0].x = Rect.right - 100 - t + 435;
			catPart[0].y = Rect.bottom - 180 - tDiag;
			catPart[1].x = Rect.right - 100 - t + 435;
			catPart[1].y = Rect.bottom - 260 - tDiag;
			catPart[2].x = Rect.right - 150 - t + 435;
			catPart[2].y = Rect.bottom - 260 - tDiag;
			catPart[3].x = Rect.right - 150 - t + 435;
			catPart[3].y = Rect.bottom - 180 - tDiag;
			Polygon(hDc, catPart, 4);
			Ellipse(hDc, Rect.right - 150 - t + 435, Rect.bottom - 285 - tDiag, Rect.right - 100 - t + 435, Rect.bottom - 235 - tDiag);

			//Голова
			catPart[0].x = Rect.right - 370 - t + 435;
			catPart[0].y = Rect.bottom - 150 - tDiag;
			catPart[1].x = Rect.right - 210 - t + 435;
			catPart[1].y = Rect.bottom - 210 - tDiag;
			catPart[2].x = Rect.right - 250 - t + 435;
			catPart[2].y = Rect.bottom - 305 - tDiag;
			catPart[3].x = Rect.right - 410 - t + 435;
			catPart[3].y = Rect.bottom - 245 - tDiag;
			Polygon(hDc, catPart, 4);

			//Уши
			catPart[0].x = Rect.right - 410 - t + 435;
			catPart[0].y = Rect.bottom - 245 - tDiag;
			catPart[1].x = Rect.right - 300 - t + 435;
			catPart[1].y = Rect.bottom - 245 - tDiag;
			catPart[2].x = Rect.right - 435 - t + 435;
			catPart[2].y = Rect.bottom - 305 - tDiag;
			Polygon(hDc, catPart, 3);

			catPart[0].x = Rect.right - 250 - t + 435;
			catPart[0].y = Rect.bottom - 305 - tDiag;
			catPart[1].x = Rect.right - 325 - t + 435;
			catPart[1].y = Rect.bottom - 245 - tDiag;
			catPart[2].x = Rect.right - 275 - t + 435;
			catPart[2].y = Rect.bottom - 365 - tDiag;
			Polygon(hDc, catPart, 3);
			}
		}
		else
		{
		//Туловище
		catPart[0].x = Rect.right - 100 - t + 435;
		catPart[0].y = Rect.bottom - 100 - tDiag;
		catPart[1].x = Rect.right - 100 - t + 435;
		catPart[1].y = Rect.bottom - 180 - tDiag;
		catPart[2].x = Rect.right - 300 - t + 435;
		catPart[2].y = Rect.bottom - 180 - tDiag;
		catPart[3].x = Rect.right - 300 - t + 435;
		catPart[3].y = Rect.bottom - 100 - tDiag;
		Polygon(hDc, catPart, 4);

		//Ножка задняя
		catPart[0].x = Rect.right - 100 - t + 435;
		catPart[0].y = Rect.bottom - 50 - tDiag;
		catPart[1].x = Rect.right - 100 - t + 435;
		catPart[1].y = Rect.bottom - 100 - tDiag;
		catPart[2].x = Rect.right - 150 - t + 435;
		catPart[2].y = Rect.bottom - 100 - tDiag;
		catPart[3].x = Rect.right - 150 - t + 435;
		catPart[3].y = Rect.bottom - 50 - tDiag;
		Polygon(hDc, catPart, 4);
		Ellipse(hDc, Rect.right - 150 - t + 435, Rect.bottom - 75 - tDiag, Rect.right - 100 - t + 435, Rect.bottom - 25 - tDiag);

		//Ножка передняя
		catPart[0].x = Rect.right - 250 - t + 435;
		catPart[0].y = Rect.bottom - 50 - tDiag;
		catPart[1].x = Rect.right - 250 - t + 435;
		catPart[1].y = Rect.bottom - 100 - tDiag;
		catPart[2].x = Rect.right - 300 - t + 435;
		catPart[2].y = Rect.bottom - 100 - tDiag;
		catPart[3].x = Rect.right - 300 - t + 435;
		catPart[3].y = Rect.bottom - 50 - tDiag;
		Polygon(hDc, catPart, 4);
		Ellipse(hDc, Rect.right - 300 - t + 435, Rect.bottom - 75 - tDiag, Rect.right - 250 - t + 435, Rect.bottom - 25 - tDiag);

		//Хвост
		catPart[0].x = Rect.right - 300 - t + 435;
		catPart[0].y = Rect.bottom - 180 - tDiag;
		catPart[1].x = Rect.right - 300 - t + 435;
		catPart[1].y = Rect.bottom - 260 - tDiag;
		catPart[2].x = Rect.right - 250 - t + 435;
		catPart[2].y = Rect.bottom - 260 - tDiag;
		catPart[3].x = Rect.right - 250 - t + 435;
		catPart[3].y = Rect.bottom - 180 - tDiag;
		Polygon(hDc, catPart, 4);
		Ellipse(hDc, Rect.right - 300 - t + 435, Rect.bottom - 285 - tDiag, Rect.right - 250 - t + 435, Rect.bottom - 235 - tDiag);

		//Голова
		catPart[0].x = Rect.right - 70 - t + 435;
		catPart[0].y = Rect.bottom - 150 - tDiag;
		catPart[1].x = Rect.right - 230 - t + 435;
		catPart[1].y = Rect.bottom - 210 - tDiag;
		catPart[2].x = Rect.right - 190 - t + 435;
		catPart[2].y = Rect.bottom - 305 - tDiag;
		catPart[3].x = Rect.right - 30 - t + 435;
		catPart[3].y = Rect.bottom - 245 - tDiag;
		Polygon(hDc, catPart, 4);

		//Уши
		catPart[0].x = Rect.right - 30 - t + 435;
		catPart[0].y = Rect.bottom - 245 - tDiag;
		catPart[1].x = Rect.right - 140 - t + 435;
		catPart[1].y = Rect.bottom - 245 - tDiag;
		catPart[2].x = Rect.right - 5 - t + 435;
		catPart[2].y = Rect.bottom - 305 - tDiag;
		Polygon(hDc, catPart, 3);

		catPart[0].x = Rect.right - 190 - t + 435;
		catPart[0].y = Rect.bottom - 305 - tDiag;
		catPart[1].x = Rect.right - 115 - t + 435;
		catPart[1].y = Rect.bottom - 245 - tDiag;
		catPart[2].x = Rect.right - 165 - t + 435;
		catPart[2].y = Rect.bottom - 365 - tDiag;
		Polygon(hDc, catPart, 3);
		}

		DeleteObject(catPen);
		DeleteObject(catBrush);

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