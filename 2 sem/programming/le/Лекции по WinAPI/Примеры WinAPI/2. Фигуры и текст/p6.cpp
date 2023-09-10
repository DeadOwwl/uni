/*Пример 2-1. Вывод текста и простых геометрических фигур*/
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

/*Прототипы используемых в программе функций пользователя*/
BOOL OnCreate(HWND,LPCREATESTRUCT);
void OnPaint(HWND);
void OnDestroy(HWND);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

/*Глобальные переменные, доступные всем функциям*/
HPEN hRedPen,hGreenPen,hBluePen;//Дескрипторы новых перьев
HBRUSH hRedBrush,hGreenBrush, hBlueBrush;//и новых кистей

/*Главная функция WinMain*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	  setlocale(LC_ALL,".1251");
	  wchar_t szClassName[]=L"MainWindow";
	  wchar_t szTitle[]=L"Program 2-1";
	  MSG msg;
	  WNDCLASS wc;
	
	  /*Зарегистрируем класс главного окна*/
	  ZeroMemory(&wc,sizeof(wc));
	  wc.lpfnWndProc=WndProc;
	  wc.hInstance=hInst;
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	  wc.hbrBackground=CreateSolidBrush(RGB(200,200,100));
	  wc.lpszClassName=szClassName;
	  RegisterClass(&wc);
	
	  /*Создадим главное окно и сделаем его видимым*/
	  HWND hwnd=CreateWindow(szClassName,szTitle,
				WS_OVERLAPPEDWINDOW,20,20,500,190,
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
	  switch(msg)  {
		HANDLE_MSG(hwnd,WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
		HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
		default:
		  return(DefWindowProc(hwnd,msg,wParam,lParam));
		}
}

/*Функия OnCreate обработки сообщений WM_CREATE*/
BOOL OnCreate(HWND,LPCREATESTRUCT)
{
	/*Создадим новые перья*/
	  hRedPen=CreatePen(PS_SOLID,4,RGB(150,0,0));
	  hGreenPen=CreatePen(PS_SOLID,10,RGB(0,150,0));
	  hBluePen=CreatePen(PS_SOLID,20,RGB(0,0,150));
	/*Создадим новые кисти*/
	  hRedBrush=CreateSolidBrush(RGB(255,120,120));
	  hGreenBrush=CreateSolidBrush(RGB(120,255,120));
	  hBlueBrush=CreateSolidBrush(RGB(120,120,255));
	  return TRUE;
}

/*Функия OnPaint обработки сообщений WM_PAINT*/
void OnPaint(HWND hwnd)
{
	  PAINTSTRUCT ps;//Структура для функции BeginPaint()
	  
	  wchar_t szText1[]=L"Rectangle( )";//Просто
	  wchar_t szText2[]=L"Ellipse( )";  //надписи
	  wchar_t szText3[]=L"Pie( )";      //над
	  wchar_t szText4[]=L"Chord( )";    //фигурами
	  
	  HDC hdc=BeginPaint(hwnd,&ps);//Получим контекст устройства

	  SetBkColor(hdc,RGB(200,200,100));//Фон под текстом
	  SetTextColor(hdc,RGB(0,0,200));//Синий цвет текста

	  /*Выведем четыре строки текста*/
	  TextOut(hdc,25,5,szText1,_tcslen(szText1));
	  TextOut(hdc,155,5,szText2,_tcslen(szText2));
	  TextOut(hdc,280,5,szText3,_tcslen(szText3));
	  TextOut(hdc,395,5,szText4,_tcslen(szText4));

	  /*Выведем четыре фигуры*/
	  Rectangle(hdc,10,40,110,140);//Квадрат
	  SelectPen(hdc,hRedPen);//Выберем в контекст новое перо
	  SelectBrush(hdc,hRedBrush);//и новую кисть
	  Ellipse(hdc,130,40,230,140);//Круг
	
	  SelectPen(hdc,hGreenPen);//Выберем новое перо
	  SelectBrush(hdc,hGreenBrush);//и новую кисть
	  Pie(hdc,250,40,350,140,350,140,250,140);//Сектор

	  SelectPen(hdc,hBluePen);//Выберем новое перо
	  SelectBrush(hdc,hBlueBrush);//и новую кисть
	  Chord(hdc,370,40,470,140,470,125,370,125);//Сегмент

	  EndPaint(hwnd,&ps);//Освободим контекст устройства
}

/*Функция OnDestroy обработки сообщения WM_DESTROY*/
void OnDestroy(HWND)
{
	PostQuitMessage(0);//Завершим программу
}
