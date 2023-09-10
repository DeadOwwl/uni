#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "resource.h"

/*��������� ������� ��� �������� ����*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void OnCommand(HWND,int,HWND,UINT);
void OnDestroy(HWND);

/*��������� ������� ��� ���� �������*/
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

HINSTANCE hIn;//���������� ����������
/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  char szClassName[]="MainWindow";
  char szTitle[]="��������� 4-1";
  MSG msg;
  WNDCLASS wc;
  hIn=hInst;//�������� ���������� ����������

  /*�������������� ����� �������� ����*/
  memset(&wc,0,sizeof(wc));
  wc.lpfnWndProc=WndProc;
  wc.hInstance=hInst;
  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);
  wc.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);//��� ���� � ����� ��������
  wc.lpszClassName=szClassName;
  RegisterClass(&wc);

  /*�������� ������� ���� � ������� ��� �������*/
  HWND hwnd=CreateWindow(szClassName,szTitle,
       WS_OVERLAPPEDWINDOW,10,10,350,200,
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
  switch(msg)
  {
    HANDLE_MSG(hwnd,WM_COMMAND,OnCommand);
    HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
    default:
      return(DefWindowProc(hwnd,msg,wParam,lParam));
  }
}

/*������� OnCommand ��������� ��������� WM_COMMAND*/
void OnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {//id = ������������� ���������� ������ ����
    case ID_ABOUT: //������� ������
      DialogBox(hIn,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc);
      break;
    case ID_EXIT://��������� ����������
      DestroyWindow(hwnd);
  }
}

/*������� OnDestroy ��������� ��������� WM_DESTROY*/
void OnDestroy(HWND)
{
  PostQuitMessage(0);
 }

/*������� ������� AboutProc ����������� ����*/
BOOL CALLBACK DlgProc(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
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
BOOL DlgOnInitDialog(HWND,HWND,LPARAM)
{
  return TRUE;
}

/*������� DlgOnCommand ��������� ��������� WM_COMMAND*/
void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {//��� �������� ���������� (������)
    case IDOK://������ ������ "�������"
    case IDCANCEL://�������� ������� ����� ��� ��������� ����
		EndDialog(hwnd,0);//������� ������
  }
}
