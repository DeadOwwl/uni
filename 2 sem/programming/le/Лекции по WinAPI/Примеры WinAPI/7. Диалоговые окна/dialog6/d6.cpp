#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include "resource.h"

HPEN hPen;
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);
void DlgOnPaint(HWND);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc);
  return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch(msg)
  {
    HANDLE_MSG(hwnd,WM_INITDIALOG,DlgOnInitDialog);
    HANDLE_MSG(hwnd,WM_COMMAND,DlgOnCommand);
    HANDLE_MSG(hwnd,WM_PAINT,DlgOnPaint);
    default:
      return FALSE;
  }
}

BOOL DlgOnInitDialog(HWND,HWND,LPARAM)
{
  hPen=CreatePen(PS_SOLID,1,RGB(255,100,100));
  return TRUE;
}

void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
    if(id==IDCANCEL)
      EndDialog(hwnd,0);
}

void DlgOnPaint(HWND hwnd)
{
  PAINTSTRUCT ps;
  
  HDC hdc=BeginPaint(hwnd,&ps);

  /*Нарисуем оси координат*/
  MoveToEx(hdc,0,70,NULL);
  LineTo(hdc,180,70);//Ось Х
  MoveToEx(hdc,100,0,NULL);
  LineTo(hdc,100,150); //Ось Y

  /*Нарисуем первую эпициклоиду*/
  for(double t=0;t<6.28;t+=0.01)
  {
    int x=(2*cos(t)-3*cos(2*t))*15;
    int y=-((2*sin(t)-3*sin(2*t)))*15;
    Rectangle(hdc,x+100,70-y,x+102,72-y);
  }

  /*Нарисуем вторую эпициклоиду*/
  SelectPen(hdc,hPen);
  for(double t=0;t<6.28;t+=0.01)
  {
    int x=(2*cos(t)-1.5*cos(2*t))*15;
    int y=-((2*sin(t)-1.5*sin(2*t)))*15;
    Rectangle(hdc,x+100,70-y,x+102,72-y);
  }
  
  EndPaint(hwnd,&ps);
}

