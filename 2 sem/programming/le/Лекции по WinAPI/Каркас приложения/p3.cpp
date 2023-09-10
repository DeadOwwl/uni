/*Пример 1-1. Простейшая программа с главным окном*/
/*Операторы препроцессора*/
#include <windows.h>//Два файла с определениями, макросами
#include <windowsx.h>//и прототипами функций Windows

/*Прототип используемой в программе функции пользователя*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

/*Главная функция WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	  char szClassName[]="MainWindow";//Имя класса главного окна
	  char szTitle[]="Программа 1-1";//Заголовок окна
	  MSG msg;//Структура msg для получения сообщений Windows
	  WNDCLASS wc;//Структура wc для задания характеристик окна

	  /*Зарегистрируем класс главного окна*/
	  ZeroMemory (&wc,sizeof(wc));//Обнуление всех членов wc
	  wc.lpfnWndProc=WndProc;//Определяем оконную процедуру
	  wc.hInstance=hInst;//Дескриптор приложения
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);//Пиктограмма
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);//Курсор мыши
	  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);//Белый фон
  	  wc.lpszClassName=szClassName;
	  
	  RegisterClass(&wc);//Собственно регистрация класса окна

	  /*Создадим главное окно и сделаем его видимым*/
	  HWND hwnd=CreateWindow(LPCSTR(szClassName),//Класс окна
							LPCSTR(szTitle), WS_OVERLAPPEDWINDOW,//Заголовок, стиль окна
							10, 10, 300, 100, //Координаты, размеры
							NULL, NULL,//Родитель, меню
							hInst, NULL);//Дескриптор приложения, параметры
	  ShowWindow(hwnd, nCmd);//Покажем окно

	  /*Организуем цикл обработки сообщений*/
	  while(GetMessage(&msg,NULL,0,0))//Получить сообщение,
			DispatchMessage(&msg);//вызвать WndProc
	  return 0;//После выхода из цикла вернуться в Windows
}//Конец функции WinMain

/*Оконная функция WndProc главного окна*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	  switch(msg)
	  {//Переход по значению msg – номеру сообщения
		case WM_DESTROY://При закрытии приложения пользователем
			PostQuitMessage(0);//Завершим приложение
			return 0;//Возврат в Windows
		default://Остальные сообщения обработать по умолчанию
			return(DefWindowProc(hwnd,msg,wParam,lParam));
		}//Конец оператора switch
}//Конец функции WndProc
