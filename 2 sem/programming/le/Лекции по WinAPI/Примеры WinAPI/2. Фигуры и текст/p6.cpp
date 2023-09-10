/*������ 2-1. ����� ������ � ������� �������������� �����*/
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

/*��������� ������������ � ��������� ������� ������������*/
BOOL OnCreate(HWND,LPCREATESTRUCT);
void OnPaint(HWND);
void OnDestroy(HWND);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

/*���������� ����������, ��������� ���� ��������*/
HPEN hRedPen,hGreenPen,hBluePen;//����������� ����� ������
HBRUSH hRedBrush,hGreenBrush, hBlueBrush;//� ����� ������

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	  setlocale(LC_ALL,".1251");
	  wchar_t szClassName[]=L"MainWindow";
	  wchar_t szTitle[]=L"Program 2-1";
	  MSG msg;
	  WNDCLASS wc;
	
	  /*�������������� ����� �������� ����*/
	  ZeroMemory(&wc,sizeof(wc));
	  wc.lpfnWndProc=WndProc;
	  wc.hInstance=hInst;
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	  wc.hbrBackground=CreateSolidBrush(RGB(200,200,100));
	  wc.lpszClassName=szClassName;
	  RegisterClass(&wc);
	
	  /*�������� ������� ���� � ������� ��� �������*/
	  HWND hwnd=CreateWindow(szClassName,szTitle,
				WS_OVERLAPPEDWINDOW,20,20,500,190,
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
	  switch(msg)  {
		HANDLE_MSG(hwnd,WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
		HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
		default:
		  return(DefWindowProc(hwnd,msg,wParam,lParam));
		}
}

/*������ OnCreate ��������� ��������� WM_CREATE*/
BOOL OnCreate(HWND,LPCREATESTRUCT)
{
	/*�������� ����� �����*/
	  hRedPen=CreatePen(PS_SOLID,4,RGB(150,0,0));
	  hGreenPen=CreatePen(PS_SOLID,10,RGB(0,150,0));
	  hBluePen=CreatePen(PS_SOLID,20,RGB(0,0,150));
	/*�������� ����� �����*/
	  hRedBrush=CreateSolidBrush(RGB(255,120,120));
	  hGreenBrush=CreateSolidBrush(RGB(120,255,120));
	  hBlueBrush=CreateSolidBrush(RGB(120,120,255));
	  return TRUE;
}

/*������ OnPaint ��������� ��������� WM_PAINT*/
void OnPaint(HWND hwnd)
{
	  PAINTSTRUCT ps;//��������� ��� ������� BeginPaint()
	  
	  wchar_t szText1[]=L"Rectangle( )";//������
	  wchar_t szText2[]=L"Ellipse( )";  //�������
	  wchar_t szText3[]=L"Pie( )";      //���
	  wchar_t szText4[]=L"Chord( )";    //��������
	  
	  HDC hdc=BeginPaint(hwnd,&ps);//������� �������� ����������

	  SetBkColor(hdc,RGB(200,200,100));//��� ��� �������
	  SetTextColor(hdc,RGB(0,0,200));//����� ���� ������

	  /*������� ������ ������ ������*/
	  TextOut(hdc,25,5,szText1,_tcslen(szText1));
	  TextOut(hdc,155,5,szText2,_tcslen(szText2));
	  TextOut(hdc,280,5,szText3,_tcslen(szText3));
	  TextOut(hdc,395,5,szText4,_tcslen(szText4));

	  /*������� ������ ������*/
	  Rectangle(hdc,10,40,110,140);//�������
	  SelectPen(hdc,hRedPen);//������� � �������� ����� ����
	  SelectBrush(hdc,hRedBrush);//� ����� �����
	  Ellipse(hdc,130,40,230,140);//����
	
	  SelectPen(hdc,hGreenPen);//������� ����� ����
	  SelectBrush(hdc,hGreenBrush);//� ����� �����
	  Pie(hdc,250,40,350,140,350,140,250,140);//������

	  SelectPen(hdc,hBluePen);//������� ����� ����
	  SelectBrush(hdc,hBlueBrush);//� ����� �����
	  Chord(hdc,370,40,470,140,470,125,370,125);//�������

	  EndPaint(hwnd,&ps);//��������� �������� ����������
}

/*������� OnDestroy ��������� ��������� WM_DESTROY*/
void OnDestroy(HWND)
{
	PostQuitMessage(0);//�������� ���������
}
