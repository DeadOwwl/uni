#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include "resource.h"

#define PI 3.14159265358979323846
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc);
  return 0;
} 

BOOL CALLBACK DlgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg)
  {
    HANDLE_MSG(hwnd,WM_COMMAND,DlgOnCommand);
    default:
      return FALSE;
  }
}

void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
  char str[20];
  double arg;
  if(id==IDC_EDIT1)
  {
      GetDlgItemText(hwnd,IDC_EDIT1,str,19);
	  arg=atoi(str)*PI/180;
      double y=sin(arg);
      sprintf(str,"%f",y);
      SetDlgItemText(hwnd,IDC_STATIC_1,str);
  }
  if(id==IDCANCEL)
      EndDialog(hwnd,0);
}
