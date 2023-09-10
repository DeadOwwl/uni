#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
     {
     char szAppName[] = "Main" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASSEX  wc ;

     wc.cbSize        = sizeof (wc) ;
     wc.style         = CS_HREDRAW | CS_VREDRAW ;
     wc.lpfnWndProc   = WndProc ;
     wc.cbClsExtra    = 0 ;
     wc.cbWndExtra    = 0 ;
     wc.hInstance     = hInstance ;
     wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wc.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wc.lpszMenuName  = NULL ;
     wc.lpszClassName = szAppName ;
     wc.hIconSm       = LoadIcon (NULL, IDI_APPLICATION) ;

	 setlocale(LC_ALL,".1251");
	 RegisterClassEx (&wc) ;

     hwnd = CreateWindow (szAppName, "Elastic Rectangle",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, nCmdShow) ;
     //UpdateWindow (hwnd);

     while (GetMessage (&msg, NULL, 0, 0))
     {
		 TranslateMessage (&msg) ;
         DispatchMessage (&msg) ;
     }
     return msg.wParam ;
     }

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     UINT style;     
	 static HDC hdc ;
     static int x1, y1, x2, y2 ;
	 static BOOL bTracking = FALSE;
	 static HBRUSH hOldBrush;
	 static HPEN hDotPen, hOldPen;

     switch (iMsg)
          {
          case WM_CREATE :
			   style =GetClassLong(hwnd, GCL_STYLE);
               SetClassLong(hwnd, GCL_STYLE, style | CS_DBLCLKS); 
               
			   hDotPen = CreatePen(PS_DOT, 1, RGB(0,0,0));
			   hdc = GetDC (hwnd) ;

			   hOldBrush = (HBRUSH)SelectObject (hdc, GetStockObject (HOLLOW_BRUSH)) ;
               break;

          case WM_LBUTTONDOWN :
			   bTracking = TRUE;
			   SetROP2(hdc, R2_NOTXORPEN);
			   x1 = x2 = LOWORD(lParam);
			   y1 = y2 = HIWORD(lParam);
			   hOldPen = (HPEN)SelectObject (hdc, hDotPen) ;
			   Rectangle (hdc, x1, y1, x2, y2); 
			   break ;

          case WM_LBUTTONUP : 
			   if (bTracking)
			   {
	   			   bTracking = FALSE;
				   SetROP2(hdc, R2_COPYPEN);
				   // нарисовать окончательный прямоугольник
				   x2 = LOWORD(lParam);
				   y2 = HIWORD(lParam);
				   SelectObject (hdc, hOldPen) ;
				   Rectangle (hdc, x1, y1, x2, y2); 
			   }
               break ;

          case WM_MOUSEMOVE :
			   if (bTracking)
			   {
				   // стереть предыдущий прямоугольник
				   Rectangle (hdc, x1, y1, x2, y2); 

				   // нарисовать новый прямоугольник
				   x2 = LOWORD(lParam);
				   y2 = HIWORD(lParam);
				   Rectangle (hdc, x1, y1, x2, y2); 
			   }
               break ;

		  case WM_LBUTTONDBLCLK :
   			   bTracking = FALSE;
			   x1 = LOWORD(lParam);
			   y1 = HIWORD(lParam);
			   SelectObject (hdc, hOldPen) ;
			   Rectangle (hdc, x1, y1, x1+100, y1+100); 
               break ;

		  case WM_DESTROY :
			   SelectObject (hdc, hOldBrush) ;
			   ReleaseDC(hwnd, hdc);
               PostQuitMessage (0) ;
               break ;

		  default:
			  return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
          }
     return 0 ;
     }
