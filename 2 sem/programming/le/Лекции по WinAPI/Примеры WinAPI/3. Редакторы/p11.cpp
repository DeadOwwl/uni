#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
     {
     char szAppName[] = "Typer" ;
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

     hwnd = CreateWindow (szAppName, "Typing Program",
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
     HDC         hdc ;
     PAINTSTRUCT ps ;
     TEXTMETRIC  tm ;

	 static string text ; //буфер для хранения введенного текста
	 string symb;

	 static char *pBuffer = NULL ;
     static int cxChar, cyChar, cxClient, cyClient;
     static int nCharPerLine, nClientLines;
     static int xCaret=0, yCaret=0 ;
	 int curIndex;
	 int nLines; // число "полных" строк текста
	 int nTailChar; // число символов в последней строке
     int x, y, i ;

     switch (iMsg)
          {
          case WM_CREATE :
               hdc = GetDC (hwnd) ;

               SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
               GetTextMetrics (hdc, &tm) ;
               cxChar = tm.tmAveCharWidth ;
               cyChar = tm.tmHeight ;

               ReleaseDC (hwnd, hdc) ;
               break;

          case WM_SIZE :  
			  // obtain window size in pixels
               cxClient = LOWORD (lParam) ;
               cyClient = HIWORD (lParam) ;

               // calculate window size in characters
               nCharPerLine = max (1, cxClient / cxChar) ;
               nClientLines = max (1, cyClient / cyChar) ;

               if (hwnd == GetFocus ())
                    SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;

               break;

          case WM_SETFOCUS :
               // create and show the caret
               CreateCaret (hwnd, NULL, cxChar, cyChar) ;
               SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
               ShowCaret (hwnd) ;
               break;

          case WM_KILLFOCUS :
               // hide and destroy the caret
               HideCaret (hwnd) ;
               DestroyCaret () ;
               break;

          case WM_KEYDOWN :
               nLines = text.size() / nCharPerLine;
			   nTailChar = text.size() % nCharPerLine;
			  switch (wParam)
                    {
                    case VK_HOME :
                         xCaret = 0 ;
                         break ;

                    case VK_END :
						 if (yCaret == nLines) 
                           xCaret = nTailChar;
						 else
                           xCaret = nCharPerLine - 1 ;
                         break ;

                    case VK_PRIOR :
                         yCaret = 0 ;
                         break ;

                    case VK_NEXT :
                         yCaret = nLines;
						 xCaret = nTailChar;
                         break ;

                    case VK_LEFT :
                         xCaret = max (xCaret - 1, 0) ;
                         break ;

                    case VK_RIGHT :
                         xCaret = min (xCaret + 1, nCharPerLine - 1) ;
						 if ((yCaret == nLines) && (xCaret > nTailChar))
							 xCaret = nTailChar;
                         break ;

                    case VK_UP :
                         yCaret = max (yCaret - 1, 0) ;
                         break ;

                    case VK_DOWN :
                         yCaret = min (yCaret + 1, nClientLines - 1) ;
						 if ((yCaret == nLines) && (xCaret > nTailChar))
							 xCaret = nTailChar;
                         break ;

                    case VK_DELETE :
                        curIndex = yCaret * nCharPerLine + xCaret; 
						if (curIndex <text.size())
						{
							text.erase(curIndex, 1);
							InvalidateRect(hwnd, NULL, TRUE);
						}
                         break ;
                    }

               SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
               break ;

          case WM_CHAR :
                switch (wParam)
                     {
                     case '\b' :                    // backspace
                          if (xCaret > 0)
                               {
                               xCaret-- ;
                               SendMessage (hwnd, WM_KEYDOWN,
                                            VK_DELETE, 1L) ;
                               }
                          break ;

                     case '\t' :                    // tab
                          do
                               {
                               SendMessage (hwnd, WM_CHAR, ' ', 1L) ;
                               }
                          while (xCaret % 8 != 0) ;
                          break ;

                     case '\r' : case '\n' :                    // carriage return & line feed
						  for (i=0; i<nCharPerLine - xCaret; ++i)
							  text += ' ';
                          xCaret = 0 ;

                          if (++yCaret == nClientLines)
						  {
                               MessageBox(hwnd, "Нет места в окне", "Error", MB_OK);
							   yCaret--;
						  }
                          break ;

					 default :                       // character codes
                        curIndex = yCaret * nCharPerLine + xCaret; 
						if (curIndex == text.size())
							text += (char)wParam;
						else {
							symb = (char)wParam;
							text.insert(curIndex,symb);
						}

						InvalidateRect(hwnd, NULL, TRUE);
                        if (++xCaret == nCharPerLine)
                        {
                             xCaret = 0 ;
                             if (++yCaret == nClientLines)
							  {
								   MessageBox(hwnd, "Нет места в окне", "Error", MB_OK);
								   yCaret--;
							  }
                        }
                        break ;
                     }

               SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
               break ;

          case WM_PAINT :
               hdc = BeginPaint (hwnd, &ps) ;
               SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;

			   if (text.size())
			   {
				   nLines = text.size() / nCharPerLine;
				   nTailChar = text.size() % nCharPerLine;
				   for (y = 0 ; y < nLines ; y++)
					   TextOut (hdc, 0, y * cyChar, text.c_str() + y*nCharPerLine, nCharPerLine) ;

			       TextOut (hdc, 0, y * cyChar, text.c_str() + y*nCharPerLine, nTailChar) ;
			   }

               EndPaint (hwnd, &ps) ;
               break ;

          case WM_DESTROY :
               PostQuitMessage (0) ;
               break ;

		  default:
			  return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
          }
     return 0 ;
     }
