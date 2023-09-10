/*************************************************************
Файл APIWin.c
Copyright (c) 1996 Мешков А., Тихомиров Ю.
*************************************************************/

/* имя приложения */
#define APPNAME "APIWIN"

#include <windows.h>         /* описание функций Win32® API */
#include "resource.h"        /* определение идентификаторов */

/* макро для определения версии системы */ 
#if defined (WIN32)
  #define IS_WIN32 TRUE
#else
  #define IS_WIN32 FALSE
#endif
#define IS_NT IS_WIN32 && (BOOL)(GetVersion() < 0x80000000)
#define IS_WIN32S IS_WIN32 && (BOOL)(!(IS_NT) && \
                  LOBYTE(LOWORD(GetVersion()))<4)
#define IS_WIN95 (BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32

/* глобальные переменные */
HINSTANCE hInst;                /* идентификатор приложения */
HWND hwndEdit;              /* идентификатор окно редактора */
char szAppName[] = APPNAME;               /* имя приложения */
/* заголовок главного окна */
char szTitle[] = APPNAME": Приложение-пример"; 

CHAR szFileName[_MAX_PATH];
CHAR szFileTitle[_MAX_PATH];

/* определение используемых функций */
ATOM APIWinRegisterClass(CONST WNDCLASS *);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL LoadFile(HANDLE hwnd, BOOL bFileNew);
BOOL SaveFile(HANDLE hwnd, BOOL bSaveAs);

/*
   первая функция приложения - инициализирует приложение и 
   выполняет цикл обработки сообщений
*/
int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, 
                   int nCmdShow)
{
  MSG msg;
  HANDLE hAccelTable;

  if (!hPrevInstance) 
  {
    /* инициализируем данные окна и регистрируем его */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }

  /* инициализируем приложение */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);
  
  hAccelTable = LoadAccelerators (hInstance, szAppName);

  /* Цикл обработки сообщений */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) 
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (msg.wParam);
}

/*
   функция регистрации оконного класса (для Windows 95)
*/
ATOM APIWinRegisterClass(CONST WNDCLASS *lpwc)
{
  HANDLE  hMod;
  FARPROC proc;
  WNDCLASSEX wcex;

  hMod = GetModuleHandle ("USER32");
  if (hMod != NULL) 
  {
#if defined (UNICODE)
    proc = GetProcAddress (hMod, "RegisterClassExW");
#else
    proc = GetProcAddress (hMod, "RegisterClassExA");
#endif

    if (proc != NULL) 
    {
      wcex.style         = lpwc->style;
      wcex.lpfnWndProc   = lpwc->lpfnWndProc;
      wcex.cbClsExtra    = lpwc->cbClsExtra;
      wcex.cbWndExtra    = lpwc->cbWndExtra;
      wcex.hInstance     = lpwc->hInstance;
      wcex.hIcon         = lpwc->hIcon;
      wcex.hCursor       = lpwc->hCursor;
      wcex.hbrBackground = lpwc->hbrBackground;
      wcex.lpszMenuName  = lpwc->lpszMenuName;
      wcex.lpszClassName = lpwc->lpszClassName;

      /* добавляем элемент нужный для Windows 95 */
      wcex.cbSize = sizeof(WNDCLASSEX);
      wcex.hIconSm = LoadIcon(wcex.hInstance, "APIWIN_SMALL");
      
      return (*proc)(&wcex);
    }
  }

  return (RegisterClass(lpwc));
}

/*
   функция инициализации данных окна и его регистрируции
*/
BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  HWND hwnd;

  /* в Win32 API параметр hPrevInstance всегда равен NULL, 
     поэтому для нахождения ранее запущенного приложения 
     используем функция поиска окна (если не хотим 
     повторного запуска приложения */
  hwnd = FindWindow (szAppName, NULL);
  if (hwnd) 
  {
    /* нашли копию приложения - восстановим его на экране и
       активизируем его */
    if (IsIconic(hwnd)) 
      ShowWindow(hwnd, SW_RESTORE);
      
    SetForegroundWindow (hwnd);

    /* данная копия должна быть завершена */
    return (FALSE);
  }

  wc.style         =  CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon (hInstance, szAppName);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszMenuName  = szAppName;
  wc.lpszClassName = szAppName;

  if (IS_WIN95) 
    return APIWinRegisterClass(&wc);
  else
    return RegisterClass(&wc);
} 

/*
   функция создания главного окна
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  
  hInst = hInstance;

  hWnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
    NULL, NULL, hInstance, NULL);

  if (!hWnd) 
    return (FALSE);
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return (TRUE);
}

/*
   функция главного окна
   обрабатывает следующие сообщения:
     WM_CREATE - создание окна
     WM_SIZE - изменение размера окна
     WM_COMMAND - обработка пользовательских команд
     WM_DESTROY - команда на завершение приложения
*/
LRESULT CALLBACK WndProc(
  HWND hWnd, 
  UINT message, 
  WPARAM wParam, 
  LPARAM lParam)
{
  int wmId, wmEvent;
  RECT rc;

  switch (message) 
  { 
    case WM_CREATE:
      /* создаем окно редактора */
      hwndEdit = CreateWindow ("edit",
      NULL,
      WS_CHILD|WS_HSCROLL|WS_MAXIMIZE|WS_VISIBLE|WS_VSCROLL|
      ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE,
      0, 0, 0, 0,
      hWnd, GetMenu(hWnd),
      hInst, NULL);

      SetFocus (hwndEdit);
      break;
    case WM_SIZE:
       /* при изменении размеров главного окна 
          изменяем и окно редактора */
       GetClientRect(hWnd, &rc);
       MoveWindow(hwndEdit, 
                  rc.left, rc.top, 
                  rc.right-rc.left,
                  rc.bottom-rc.top, TRUE);
       break;
    case WM_COMMAND:
      wmId = LOWORD(wParam); 
      wmEvent = HIWORD(wParam); 

      /* разбор команд меню */
      switch (wmId) 
      {
        case IDM_EXIT:
          DestroyWindow (hWnd);
          break;

        case IDM_NEW:
          LoadFile(hWnd, TRUE);
          break;

        case IDM_OPEN:
          LoadFile(hWnd, FALSE);
          break;

        case IDM_SAVE:
          SaveFile(hWnd, FALSE);
          break;

        case IDM_SAVEAS:
          SaveFile(hWnd, TRUE);
          break;

        /* команды которые пока не обрабатываем */
        default:
          return (DefWindowProc(
            hWnd, message, wParam, lParam));
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return (0);
}

/*
   функция для загрузки содержимого файла или 
   очистки редактора
*/
BOOL LoadFile(HANDLE hwnd, BOOL bFileNew)
{
  OPENFILENAME ofn;
  DWORD dwFileSize;
  HGLOBAL hBuffer;
  LPSTR lpBuffer;
  HANDLE hFile;

  if (bFileNew)
  {
    szFileName[0] = '\0';
    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"");
  }
  else
  {
    memset(&ofn, 0, sizeof(ofn));

    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = GetActiveWindow();
    ofn.lpstrFilter       = "Все файлы(*.*)\0*.*\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile         = szFileName;
    ofn.nMaxFile          = _MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = szFileTitle;
    ofn.nMaxFileTitle     = _MAX_PATH;
    ofn.lpstrTitle        = "Открытие файла";
    ofn.lpstrDefExt       = NULL;
    ofn.Flags             = OFN_FILEMUSTEXIST | 
                            OFN_HIDEREADONLY;

    /* используем стандартный диалог */
    GetOpenFileName ((LPOPENFILENAME)&ofn);

    /* открываем файл по имени */
    hFile = CreateFile(szFileName, GENERIC_READ,
      0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    /* определяем длину файла */
    dwFileSize = GetFileSize(hFile, NULL);

    /* создаем буфер для чтения из файла */
    hBuffer = GlobalAlloc(GHND, dwFileSize+1);
    lpBuffer = (LPSTR)GlobalLock(hBuffer);

    /* читаем содержимое файла */
    ReadFile(hFile, lpBuffer, dwFileSize, &dwFileSize, NULL);
    lpBuffer[dwFileSize] = '\0';

    /* заполняем окно редактора */
    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)lpBuffer);

    /* освобождаем буфер */ 
    GlobalUnlock(lpBuffer);
    GlobalFree(hBuffer);

    /* закрываем файл */
    CloseHandle(hFile);
  }

  return TRUE;
}

/*
   функция для сохранения содержимого редактора
   в файле
*/
BOOL SaveFile(HANDLE hwnd, BOOL bSaveAs)
{
  OPENFILENAME ofn;
  DWORD dwFileSize;
  HGLOBAL hBuffer;
  LPSTR lpBuffer;
  HANDLE hFile;

  if (bSaveAs)
  {
    memset(&ofn, 0, sizeof(ofn));

    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hwnd;
    ofn.lpstrFilter       = "Все файлы(*.*)\0*.*\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile         = szFileName;
    ofn.nMaxFile          = _MAX_PATH;
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrFileTitle    = szFileTitle;
    ofn.nMaxFileTitle     = _MAX_PATH;
    ofn.Flags             = OFN_OVERWRITEPROMPT |
                            OFN_HIDEREADONLY;

    /* Используем стандартный диалог */
    GetSaveFileName((LPOPENFILENAME)&ofn);
  }

  /* открываем или создаем, если не существует, 
     файл по имени */
  hFile = CreateFile(szFileName, GENERIC_WRITE,
    0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  /* удаляем содержимое файла */
  SetEndOfFile(hFile);

  /* определяем размер текста в редакторе */
  dwFileSize = SendMessage(hwndEdit, WM_GETTEXTLENGTH, 0, 0);

  /* создаем буфер для чтения из буфера редактора */
  hBuffer = GlobalAlloc(GHND, dwFileSize+1);
  lpBuffer = (LPSTR)GlobalLock(hBuffer);

  /* читаем содержимое буфера */
  SendMessage(hwndEdit, WM_GETTEXT, 
    dwFileSize+1, (LPARAM)lpBuffer);

  /* записываем буфер в файл */
  WriteFile(hFile, lpBuffer, dwFileSize, &dwFileSize, NULL);

  /* освобождаем буфер */ 
  GlobalUnlock(lpBuffer);
  GlobalFree(hBuffer);

  /* закрываем файл */
  CloseHandle(hFile);

  return TRUE;
}
