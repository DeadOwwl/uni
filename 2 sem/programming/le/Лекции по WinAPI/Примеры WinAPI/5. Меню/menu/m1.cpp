#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include "resource.h"

HBRUSH hBlueBrush,hGreenBrush;//Дескрипторы кистей фона
int sw;//Переключатель для управления фоном окна
/*Главная функция WinMain*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	  char szClassName[]="MainWindow";
	  char szTitle[]="Меню1";
	  MSG msg;
	  WNDCLASS wc;
	  HACCEL hAccel;
	  
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
		  WS_OVERLAPPEDWINDOW,10,10,200,100,
		  HWND_DESKTOP,NULL,hInst,NULL);

	  hAccel = LoadAccelerators(hInst,MAKEINTRESOURCE(IDR_ACCELERATOR1));
	  ShowWindow(hwnd,SW_SHOWNORMAL);
	  UpdateWindow(hwnd);
	
	  /*Организуем цикл обработки сообщений*/
	  while(GetMessage(&msg,NULL,0,0))
	  {
       if(!TranslateAccelerator(hwnd,hAccel,&msg)) // преобразует сообщения от клавиатуры в 
	   {											// WM_COMMAND
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	   }
	  }
	  return 0;
  }

/*Оконная функция WndProc главного окна*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;//Структура для функции BeginPaint()
	HDC hdc;
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
		    case ID_Exit:
			   DestroyWindow(hwnd);
		}
		break;
	
	case WM_CREATE: 
		hBlueBrush=CreateSolidBrush(RGB(100,100,255));
		hGreenBrush=CreateSolidBrush(RGB(100,255,100));
		break;
    
	case WM_PAINT: 
		hdc=BeginPaint(hwnd,&ps);//Получим контекст устройства
		if(sw==1)//Если выбрано "Синий"
			FillRect(hdc,&ps.rcPaint,hBlueBrush);
		if(sw==2)//Если выбрано "Зеленый"
			FillRect(hdc,&ps.rcPaint,hGreenBrush);
		EndPaint(hwnd,&ps);//Освободим контекста устройства
		break;
    
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
    
	default:
		return(DefWindowProc(hwnd,msg,wParam,lParam));
    }
  return 0;
}

