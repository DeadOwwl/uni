#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc);//Откроем диалог
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
  char str[100];
  for (double x=0;x<5;x+=0.1){
    sprintf(str,"%f    %f",x,exp(-x));
    SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)str);
    }
  return TRUE;
}

void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {
    case IDCANCEL:
      EndDialog(hwnd,0);//Закроем диалог
  }
}
