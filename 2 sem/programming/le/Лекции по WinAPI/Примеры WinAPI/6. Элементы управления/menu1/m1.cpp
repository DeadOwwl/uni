#pragma comment (lib,"comctl32.lib")
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

//#define MAX_MENUS 5

//static POPUPSTRING popstr[MAX_MENUS];

HBRUSH hBlueBrush,hGreenBrush;//����������� ������ ����
int sw;//������������� ��� ���������� ����� ����

HWND hwndStatusBar = NULL;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
//LRESULT Statusbar_MenuSelect (HINSTANCE,HWND,WPARAM,LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	  char szClassName[]="MainWindow";
	  char szTitle[]="����1";
	  MSG msg;
	  WNDCLASS wc;
	/*�������������� ����� �������� ����*/
	  ZeroMemory(&wc,sizeof(wc));
	  wc.lpfnWndProc=WndProc;
	  wc.hInstance=hInst;
	  wc.style = CS_HREDRAW | CS_VREDRAW;
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);
	  wc.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);//��� ���� � ����� ��������
	  wc.lpszClassName=szClassName;
	  RegisterClass(&wc);
	
	  /*�������� ������� ���� � ������� ��� �������*/
	  HWND hwnd=CreateWindow(szClassName,szTitle,
		  WS_OVERLAPPEDWINDOW,100,100,400,200,
		  HWND_DESKTOP,NULL,hInst,NULL);
	  ShowWindow(hwnd,SW_SHOWNORMAL);
	
	  /*���������� ���� ��������� ���������*/
	  while(GetMessage(&msg,NULL,0,0))
		DispatchMessage(&msg);
	  return 0;
  }

/*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;//��������� ��� ������� BeginPaint()
	HDC hdc;
	static HMENU hMenu;
	HMENU hClickMenu;
	int itemID;
	static UINT submenuID;
	char text[200];

	switch(msg){
	case WM_COMMAND: 
		switch(LOWORD (wParam))
		{
			case ID_Blue:
			   sw=1;
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;

			case ID_Green:
			   sw=2;
			   InvalidateRect(hwnd,NULL,TRUE);
			   break;

			case ID_About:
				MessageBox(hwnd, "Version1.0\nCopyright 2009","� ���������", MB_OK);
			   break;

			case ID_Exit:
			   DestroyWindow(hwnd);
		}
		SendMessage(hwndStatusBar, SB_SIMPLE, FALSE, 0);
		break;
	
    case WM_MENUSELECT :
		itemID = LOWORD(wParam);
		hClickMenu = (HMENU)lParam;
		if (HIWORD(wParam) & MF_POPUP)
		{
			if (hClickMenu == hMenu)
				submenuID = itemID;
			else
				itemID+=(submenuID+1);
		}
		else if (!itemID)
			   itemID=-1;
		SendMessage(hwndStatusBar, SB_SIMPLE, TRUE, 0);
		LoadString(GetModuleHandle(NULL), itemID, text, 200);
		SendMessage(hwndStatusBar, SB_SETTEXT, 255, (LPARAM)text); 

		break;

	case WM_CREATE: 
		hBlueBrush=CreateSolidBrush(RGB(100,100,255));
		hGreenBrush=CreateSolidBrush(RGB(100,255,100));
		hMenu = GetMenu(hwnd);

		hwndStatusBar = CreateStatusWindow (WS_CHILD | WS_VISIBLE,"������", hwnd, 
                                  ID_STATUS_BAR) ;
		break;
    
	case WM_SIZE: // ��� ��������� �������� ����
		SendMessage(hwndStatusBar, WM_SIZE, wParam, lParam);
		break;

	case WM_PAINT: 
		hdc=BeginPaint(hwnd,&ps);//������� �������� ����������
		if(sw==1)//���� ������� "�����"
			FillRect(hdc,&ps.rcPaint,hBlueBrush);
		if(sw==2)//���� ������� "�������"
			FillRect(hdc,&ps.rcPaint,hGreenBrush);
		EndPaint(hwnd,&ps);//��������� ��������� ����������
		break;
    
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
    
	default:
		return(DefWindowProc(hwnd,msg,wParam,lParam));
    }
  return 0;
}