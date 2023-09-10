#pragma comment (lib,"Gdi32.lib")
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInstance;

int iCurrentColor  = ID_WHITE;
static COLORREF crColor[3] = { RGB (255, 255 , 255), RGB (  0,   255, 0),
                               RGB (0, 0, 255) } ;
static char szFilter[] = "Text Files (*.TXT)\0*.txt\0"  \
                         "All Files (*.*)\0*.*\0\0" ;
HBRUSH hBrush;

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	  char szClassName[]="MainWindow";
	  char szTitle[]="Меню и диалог";
	  MSG msg;
	  WNDCLASS wc;
	  hInstance = hInst;
	  
	/*Зарегистрируем класс главного окна*/
	  ZeroMemory(&wc,sizeof(wc));
	  wc.lpfnWndProc=WndProc;
	  wc.hInstance=hInst;
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);
	  wc.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);//Имя меню в файле ресурсов
	  wc.lpszClassName=szClassName;
	  RegisterClass(&wc);
	
	  /*Создадим главное окно и сделаем его видимым*/
	  HWND hwnd=CreateWindow(szClassName,szTitle,
		  WS_OVERLAPPEDWINDOW,100,100,400,300,
		  HWND_DESKTOP,NULL,hInst,NULL);
	  
	  ShowWindow(hwnd,SW_SHOWNORMAL);
	
	  /*Организуем цикл обработки сообщений*/
	  while(GetMessage(&msg,NULL,0,0))
	  {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	  }
	  return 0;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rcClient;
	BOOL success;

	static COLORREF textColor;

	// Open, Save as - standard
	static OPENFILENAME ofn;
	static char szFile[MAX_PATH];

	// Color standard
	static CHOOSECOLOR cc; // common dialogbox structure
	static COLORREF acrCustClr[16]; // array of custom colors

	// Font standard
	static CHOOSEFONT chf;
	static HFONT hFont;
	static LOGFONT lf;


    switch (iMsg)
	{
          case WM_CREATE :
			  // ofn - file
			  ofn.lStructSize = sizeof(OPENFILENAME);
			  ofn.hwndOwner = hWnd;
			  ofn.lpstrFilter = szFilter ;
			  ofn.lpstrFile = szFile;
			  ofn.nMaxFile = sizeof(szFile);
              ofn.lpstrDefExt = "txt" ;

			  // cc - color
			  cc.lStructSize =sizeof(CHOOSECOLOR);
			  cc.hwndOwner = hWnd;
			  cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			  cc.rgbResult      = RGB (255, 255, 255) ;
			  cc.lpCustColors   = acrCustClr ;
			  cc.lCustData      = 0L ;

			  //chf - font
			  chf.lStructSize =sizeof(CHOOSEFONT);
			  chf.hwndOwner = hWnd;
			  chf.lpLogFont = &lf;
			  chf.nFontType = SIMULATED_FONTTYPE;
			  chf.iPointSize       = 0 ;
			  chf.Flags            = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS
														  | CF_EFFECTS ;
			  chf.rgbColors        = 0L ;
			  chf.lCustData        = 0L ;
			  chf.lpfnHook         = NULL ;
			  chf.lpTemplateName   = NULL ;
			  chf.hInstance        = NULL ;
			  chf.lpszStyle        = NULL ;
			  chf.nSizeMin         = 0 ;
			  chf.nSizeMax         = 0 ;
			  GetObject (GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),(PSTR)&lf);
			  break;

		  case WM_COMMAND :

               switch (LOWORD (wParam))
               {
                    case ID_OPEN:
						strcpy(szFile,"");
						success = GetOpenFileName(&ofn);
						if (success)
							MessageBox(hWnd, ofn.lpstrFile, "Открывается файл:", MB_OK);
						else
							MessageBox(hWnd, "GetOpenFileName",
							"Отказ от выбора или ошибка", MB_ICONWARNING);
						break;

                    case ID_SAVE_AS :
						strcpy(szFile,"");
						success = GetSaveFileName(&ofn);
						if (success)
							MessageBox(hWnd, ofn.lpstrFile, 
							           "Файл сохраняется с именем:", MB_OK);
						else
							MessageBox(hWnd, "GetSaveFileName",
							"Отказ от выбора или ошибка", MB_ICONWARNING);
						break;

                    case ID_BKGR_COLOR :
                         DialogBox (hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc);
						 SetClassLong(hWnd,GCL_HBRBACKGROUND, 
							          (LONG)CreateSolidBrush(crColor[iCurrentColor - ID_WHITE]));
                         break;

 					case ID_TEXT_COLOR :
						 if (ChooseColor(&cc)) 
							 textColor = cc.rgbResult;
                         break;

					case ID_FONT :
						 if (ChooseFont(&chf)) 
							 hFont = CreateFontIndirect(chf.lpLogFont);
                         break;

                    case ID_EXIT :
                         SendMessage (hWnd, WM_CLOSE, 0, 0L) ;
                         break;
				    
					default:
						 break;
				}
			   InvalidateRect(hWnd, NULL, TRUE);
			   break ;

          case WM_PAINT :
               hDC = BeginPaint (hWnd, &ps) ;
			   SetBkMode(hDC, TRANSPARENT);
			   SetTextColor(hDC, textColor);
			   if (hFont)
				   DeleteObject(SelectObject(hDC, hFont));

			   GetClientRect(hWnd, &rcClient);
			   DrawText(hDC,"Общие и пользовательские диалоги", -1, &rcClient,
						DT_SINGLELINE | DT_CENTER | DT_VCENTER);
               EndPaint (hWnd, &ps) ;
               break;

		  case WM_DESTROY :
               PostQuitMessage (0) ;
               break;

		  default:
			  return DefWindowProc (hWnd, iMsg, wParam, lParam) ;
    }
    return 0;
}

void PaintWindow (HWND hwnd, int iColor)
{
     HBRUSH          hBrush ;
     HDC             hdc ;
     RECT            rect ;

     hdc = GetDC (hwnd) ;
     GetClientRect (hwnd, &rect) ;
	 hBrush = CreateSolidBrush (crColor[iColor - ID_WHITE]) ;
	 hBrush = (HBRUSH) SelectObject (hdc, hBrush) ;

     Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom) ;

     DeleteObject (SelectObject (hdc, hBrush)) ;
     ReleaseDC (hwnd, hdc) ;
}


void PaintTheBlock (HWND hCtrl, int iColor)
{
     InvalidateRect (hCtrl, NULL, TRUE) ;
     UpdateWindow (hCtrl) ;
     PaintWindow (hCtrl, iColor) ;
}

BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     static HWND hCtrlBlock ;
     static int  iColor ;

     switch (iMsg)
          {
          case WM_INITDIALOG :
               iColor  = iCurrentColor ;

               CheckRadioButton (hDlg, ID_WHITE, ID_BLUE, iColor) ;
               
               hCtrlBlock = GetDlgItem (hDlg, IDC_STATIC_1) ;

               SetFocus (GetDlgItem (hDlg, iColor)) ;
               return FALSE ;

          case WM_COMMAND :
               switch (LOWORD (wParam))
                    {
                    case IDOK :
                         iCurrentColor  = iColor ;
                         EndDialog (hDlg, TRUE) ;
                         return TRUE ;
                    
					case IDCANCEL :
                         EndDialog (hDlg, FALSE) ;
                         return TRUE ;

                    case ID_WHITE :
                    case ID_GREEN :
                    case ID_BLUE :
                         iColor = LOWORD (wParam) ;
                         CheckRadioButton (hDlg, ID_WHITE, ID_BLUE, LOWORD(wParam)) ;
                         PaintTheBlock (hCtrlBlock, iColor) ;
                         return TRUE ;

                    }
               break ;

          case WM_PAINT :
               PaintTheBlock (hCtrlBlock, iColor) ;
               break ;
          }
     return FALSE ;
}



