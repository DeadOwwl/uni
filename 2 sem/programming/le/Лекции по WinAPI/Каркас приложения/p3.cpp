/*������ 1-1. ���������� ��������� � ������� �����*/
/*��������� �������������*/
#include <windows.h>//��� ����� � �������������, ���������
#include <windowsx.h>//� ����������� ������� Windows

/*�������� ������������ � ��������� ������� ������������*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	  char szClassName[]="MainWindow";//��� ������ �������� ����
	  char szTitle[]="��������� 1-1";//��������� ����
	  MSG msg;//��������� msg ��� ��������� ��������� Windows
	  WNDCLASS wc;//��������� wc ��� ������� ������������� ����

	  /*�������������� ����� �������� ����*/
	  ZeroMemory (&wc,sizeof(wc));//��������� ���� ������ wc
	  wc.lpfnWndProc=WndProc;//���������� ������� ���������
	  wc.hInstance=hInst;//���������� ����������
	  wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);//�����������
	  wc.hCursor=LoadCursor(NULL,IDC_ARROW);//������ ����
	  wc.hbrBackground=GetStockBrush(WHITE_BRUSH);//����� ���
  	  wc.lpszClassName=szClassName;
	  
	  RegisterClass(&wc);//���������� ����������� ������ ����

	  /*�������� ������� ���� � ������� ��� �������*/
	  HWND hwnd=CreateWindow(LPCSTR(szClassName),//����� ����
							LPCSTR(szTitle), WS_OVERLAPPEDWINDOW,//���������, ����� ����
							10, 10, 300, 100, //����������, �������
							NULL, NULL,//��������, ����
							hInst, NULL);//���������� ����������, ���������
	  ShowWindow(hwnd, nCmd);//������� ����

	  /*���������� ���� ��������� ���������*/
	  while(GetMessage(&msg,NULL,0,0))//�������� ���������,
			DispatchMessage(&msg);//������� WndProc
	  return 0;//����� ������ �� ����� ��������� � Windows
}//����� ������� WinMain

/*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	  switch(msg)
	  {//������� �� �������� msg � ������ ���������
		case WM_DESTROY://��� �������� ���������� �������������
			PostQuitMessage(0);//�������� ����������
			return 0;//������� � Windows
		default://��������� ��������� ���������� �� ���������
			return(DefWindowProc(hwnd,msg,wParam,lParam));
		}//����� ��������� switch
}//����� ������� WndProc
