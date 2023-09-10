#include <windows.h>
#include <windowsx.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

BOOL OnCreate(HWND,LPCREATESTRUCT);
void OnPaint(HWND);
void OnCommand(HWND,int,HWND,UINT);
void OnDestroy(HWND);

BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

HBRUSH hBlueBrush,hGreenBrush;//����������� ������ ����
int sw=1;//������������� �����, ��������� � �����
HWND hWnd;//���������� �������� ����
HINSTANCE hInst;//���������� ����������

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,int)
{
  char szClassName[]="MainWindow";
  char szTitle[]="����������� ������";
  MSG msg;
  WNDCLASS wc;
  hInst=hInstance;
  
  ZeroMemory(&wc,sizeof(wc));
  wc.lpfnWndProc=WndProc;
  wc.hInstance=hInst;
  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);
  wc.lpszClassName=szClassName;

  RegisterClass(&wc);

  hWnd=CreateWindow(szClassName,szTitle,
     WS_OVERLAPPEDWINDOW,10,10,300,180,
     HWND_DESKTOP,NULL,hInst,NULL);
   
  ShowWindow(hWnd,SW_SHOWNORMAL);

  while(GetMessage(&msg,NULL,0,0))
    DispatchMessage(&msg);
  return 0;
}

/*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg)
  {
    HANDLE_MSG(hwnd,WM_CREATE,OnCreate);
    HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
    HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
    default:
        return(DefWindowProc(hwnd,msg,wParam,lParam));
  }
}

/*������� OnCreate ��������� ��������� WM_CREATE*/
BOOL OnCreate(HWND hwnd,LPCREATESTRUCT)
{
  hBlueBrush=CreateSolidBrush(RGB(100,100,255));
  hGreenBrush=CreateSolidBrush(RGB(100,255,100));

  CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc);
  return TRUE;
}

/*������� OnPaint ��������� ��������� WM_PAINT*/
void OnPaint(HWND hwnd)
{
  PAINTSTRUCT ps;
  HDC hdc=BeginPaint(hwnd,&ps);
  
  if(sw==1)
    FillRect(hdc,&ps.rcPaint,hBlueBrush);
  if(sw==2)
    FillRect(hdc,&ps.rcPaint,hGreenBrush);
  EndPaint(hwnd,&ps);
}

/*������� OnDestroy ��������� ��������� WM_DESTROY*/
void OnDestroy(HWND)
{
  PostQuitMessage(0);
}

/*������� ������� ������������ �������*/
BOOL CALLBACK DlgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg)
  {
    HANDLE_MSG(hwnd,WM_INITDIALOG,DlgOnInitDialog);
    HANDLE_MSG(hwnd,WM_COMMAND,DlgOnCommand);
    default:
      return FALSE;
  }
}

/*������� DlgOnInitDialog ��������� ��������� WM_INITDIALOG*/
BOOL DlgOnInitDialog(HWND hwnd,HWND,LPARAM)
{
  SendDlgItemMessage(hwnd,ID_BLUE,BM_SETCHECK,TRUE,0);
  return TRUE;
}

/*������� DlgOnCommand ��������� ��������� WM_COMMAND*/
void DlgOnCommand(HWND,int id,HWND,UINT)
{
  switch(id)
  {
    case ID_BLUE:
      sw=1;
      InvalidateRect(hWnd,NULL,TRUE);
      break;
    case ID_GREEN:
      sw=2;
      InvalidateRect(hWnd,NULL,TRUE);
      break;
  }
}
