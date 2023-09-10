#include <windows.h>
#include <string>
#include <cassert>
using namespace std;


struct MyException {
    string msg;
    MyException(const string& msg=""): msg(msg) {}
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const int MAX_ARG_LEN = 200;    // ����������� �� ����� ���������

HINSTANCE hInstance;            // instance ����������
LPCSTR szClassName  = "Sample 1a";      // �������� ������ ����
LPCSTR szTitle      = "���������� 1�";  // ��������� ����������

HWND    hEditA,                 // edit ��� ��������� A 
        hEditB,                 // edit ��� ��������� B
        hEditResult,            // edit ��� ���������� (�� �������������)
        hButtonCalc,
        hRBPlus, hRBMinus, hRBMul, hRBDiv;  // radiobuttons ��� ���� ��������


// ID ��� ��������� ����������
#define ID_EDITA        3001    
#define ID_EDITB        3002
#define ID_EDITRESULT   3003
#define ID_BUTTON_CALC  3004
#define ID_RB_PLUS      3005
#define ID_RB_MINUS     3006
#define ID_RB_MUL       3007
#define ID_RB_DIV       3008

BOOL InitApplication() {
    WNDCLASS wc;
    wc.style        = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc  = (WNDPROC) WndProc;
    wc.cbClsExtra   = 0;
    wc.cbWndExtra   = 0;
    wc.hInstance    = hInstance;
    wc.hIcon        = NULL;
    wc.hCursor      = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    return RegisterClass(&wc);
}

BOOL InitInstance(int nShowCmd) {
    HWND hWnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        280, 260, // ������� ���� // CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL);
    if (!hWnd) 
        return FALSE;
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);
    return TRUE;
}

void CreateControls(HWND hWnd) {
    CreateWindow("static", "������ ��������", WS_CHILD | WS_VISIBLE | SS_LEFT, 
        12, 12, 140, 20, hWnd, 0, hInstance, NULL);
    CreateWindow("static", "������ ��������", WS_CHILD | WS_VISIBLE | SS_LEFT, 
        12, 42, 140, 20, hWnd, 0, hInstance, NULL);
    CreateWindow("static", "���������", WS_CHILD | WS_VISIBLE | SS_LEFT, 
        12, 72, 140, 20, hWnd, 0, hInstance, NULL);

    hEditA = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        155, 12, 100, 20, hWnd, (HMENU) ID_EDITA, hInstance, NULL);
    hEditB = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        155, 42, 100, 20, hWnd, (HMENU) ID_EDITB, hInstance, NULL);
    hEditResult = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        155, 72, 100, 20, hWnd, (HMENU) ID_EDITRESULT, hInstance, NULL);

    EnableWindow(hEditResult, FALSE);   // ������ ���� ���������� ����������� ��� �������������� 

    hRBPlus = CreateWindow("button", "�������", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        12, 110, 100, 20, hWnd, (HMENU) ID_RB_PLUS, hInstance, NULL);
    hRBMinus = CreateWindow("button", "�������", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        12, 140, 100, 20, hWnd, (HMENU) ID_RB_MINUS, hInstance, NULL);
    hRBMul = CreateWindow("button", "��������", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        12, 170, 100, 20, hWnd, (HMENU) ID_RB_MUL, hInstance, NULL);
    hRBDiv = CreateWindow("button", "���������", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        12, 200, 100, 20, hWnd, (HMENU) ID_RB_DIV, hInstance, NULL);

    hButtonCalc = CreateWindow("Button", "���������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        155, 190, 100, 30, hWnd, (HMENU) ID_BUTTON_CALC, hInstance, NULL);

    SendMessage(hRBPlus, BM_SETCHECK, (WPARAM) BST_CHECKED, 0); // �������� �������� "�������"

}

// ������� ������ ����� ����� �� ��������� �������� ���������� "edit"
int ReadArg(HWND hEdit) {
    char buf[MAX_ARG_LEN];
    GetWindowText(hEdit, buf, MAX_ARG_LEN); // ������
    int result = atoi(buf);                 // ��������� � ����� (����� �� �����������, ����� 0)
    sprintf(buf, "%d", result);
    SetWindowText(hEdit, buf);              // ���������� ���������� ����� �������
    return result;
}

void DoCalc() {
    try {
        int result = ReadArg(hEditA), b = ReadArg(hEditB);
        if (SendMessage(hRBPlus, BM_GETCHECK, 0, 0) == BST_CHECKED)         // ������� "�������"?
            result += b;
        else if (SendMessage(hRBMinus, BM_GETCHECK, 0, 0) == BST_CHECKED)   // ������� "�������"
            result -= b;
        else if (SendMessage(hRBMul, BM_GETCHECK, 0, 0) == BST_CHECKED)     // ������� "��������"
            result *= b;
        else if (SendMessage(hRBDiv, BM_GETCHECK, 0, 0) == BST_CHECKED) {   // ������� "���������"
            if (b == 0) throw MyException("������� �� ����!");
            result /= b;
        } else
            assert(false);

        char buf[MAX_ARG_LEN];
        sprintf(buf, "%d", result);
        SetWindowText(hEditResult, buf);
    } catch (MyException& e) {
        SetWindowText(hEditResult, "Error!");
        MessageBox(NULL, e.msg.c_str(), "Error!", MB_OK);
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            CreateControls(hWnd);       // ���� ���������
            return 0;
        case WM_DESTROY:                // ���� ���������
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:                // ��������� �� �������� ����������
            switch (LOWORD(wParam)) {   
                case ID_BUTTON_CALC:    // ��������� �� ������ "���������"
                    DoCalc();
					//MessageBox(NULL, "Click!", "Info", MB_OK);
                   return 0;
            }
            return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);    // ��������� ��������� �� ���������
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInstance = hInst;
    // �������� ����� �������� ����
    if (!InitApplication()) {
        MessageBox(NULL, "Cannot register class", "Error", MB_OK);
        return 0;
    }
    // �������� ������� ���� � ������� ���
    if (!InitInstance(nShowCmd)) {
        MessageBox(NULL, "Cannot create window", "Error", MB_OK);
        return 0;
    }
    // ���� ��������� ���������
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}
