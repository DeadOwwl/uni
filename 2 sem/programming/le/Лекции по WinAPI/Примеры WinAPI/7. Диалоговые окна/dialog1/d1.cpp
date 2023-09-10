#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "resource.h"

/*Прототипы функций для главного окна*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void OnCommand(HWND,int,HWND,UINT);
void OnDestroy(HWND);

/*Прототипы функций для окна диалога*/
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL DlgOnInitDialog(HWND,HWND,LPARAM);
void DlgOnCommand(HWND,int,HWND,UINT);

HINSTANCE hIn;//Глобальная переменная
/*Главная функция WinMain*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
  char szClassName[]="MainWindow";
  char szTitle[]="Программа 4-1";
  MSG msg;
  WNDCLASS wc;
  hIn=hInst;//Сохраним дескриптор приложения

  /*Зарегистрируем класс главного окна*/
  memset(&wc,0,sizeof(wc));
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
       WS_OVERLAPPEDWINDOW,10,10,350,200,
       HWND_DESKTOP,NULL,hInst,NULL);
  ShowWindow(hwnd,SW_SHOWNORMAL);

  /*Организуем цикл обработки сообщений*/
  while(GetMessage(&msg,NULL,0,0))
    DispatchMessage(&msg);
  return 0;
}

/*Оконная функция WndProc главного окна*/
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

/*Функция OnCommand обработки сообщений WM_COMMAND*/
void OnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {//id = идентификатор выбранного пункта меню
    case ID_ABOUT: //Открыть диалог
      DialogBox(hIn,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc);
      break;
    case ID_EXIT://Завершить приложение
      DestroyWindow(hwnd);
  }
}

/*Функция OnDestroy обработки сообщения WM_DESTROY*/
void OnDestroy(HWND)
{
  PostQuitMessage(0);
 }

/*Оконная функция AboutProc диалогового окна*/
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

/*Функция DlgOnInitDialog обработки сообщения WM_INITDIALOG*/
BOOL DlgOnInitDialog(HWND,HWND,LPARAM)
{
  return TRUE;
}

/*Функция DlgOnCommand обработки сообщений WM_COMMAND*/
void DlgOnCommand(HWND hwnd,int id,HWND,UINT)
{
  switch(id)
  {//Код элемента управления (кнопки)
    case IDOK://Нажата кнопка "Закрыть"
    case IDCANCEL://Закрытие диалога через его системное меню
		EndDialog(hwnd,0);//Закрыть диалог
  }
}
