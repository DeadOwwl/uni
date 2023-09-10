#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

int result;

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  for(int i=0;i<1000;i++)
    result+=i;//������� ���������
  DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc);//������� ������

  return 0;
}

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

BOOL DlgOnInitDialog(HWND hwnd,HWND,LPARAM)
{
  char szText[100]="����� ����� = ";//������ ������
  char res[20];//������ ��� �������������� ����������

  itoa(result,res,10);//����������� ��������� � ������
  strcat(szText,res);//�������� ������ ������
  SetDlgItemText(hwnd,IDC_STATIC_1,szText);//������� � ������

  return TRUE;
}

void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {
    case IDOK: case IDCANCEL:
      EndDialog(hwnd,0);//������� ������
  }
}
