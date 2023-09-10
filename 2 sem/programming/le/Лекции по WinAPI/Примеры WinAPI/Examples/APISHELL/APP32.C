/*************************************************************
Файл APIShell.c
Copyright (c) 1996 Мешков А., Тихомиров Ю.
*************************************************************/

#define _INC_OLE
#include <windows.h>
#undef  _INC_OLE

#include <windowsx.h>

#include "resource.h"

/* определение номера сообщения */
#define WM_NOTIFYICON    (WM_APP+100)

HINSTANCE g_hinst;
UINT g_uState;

/* идентификатор пиктограммы */
#define IDC_NOTIFY 1000

/*
   объявления используемых функций 
*/

/* оконная функция окна диалога */
BOOL CALLBACK TestAppDlgProc(HWND hDlg, UINT uMsg, 
                             WPARAM wParam, LPARAM lParam);
/* функция настройки уведомляющей области */
BOOL TrayMessage(HWND hDlg, DWORD dwMessage, 
                 HICON hIcon, PSTR pszTip);
/* функция изменения состояния пиктограммы уведомления */
void StateChange(HWND hDlg);

/*
   реализация функций приложения
*/
int WINAPI WinMain(
  HINSTANCE hInstance, 
  HINSTANCE hPrevInstance, 
  LPSTR lpCmdLine, 
  int nCmdShow)
{
/* сохраняем дескриптор приложения, не проверяя
   наличие предыдущих копий */
  g_hinst = hInstance;

/* создание и вывод диалога настройки - 
   основного окна приложения */
  DialogBox(
    hInstance, 
    MAKEINTRESOURCE(IDD_APISHELL), 
    NULL, 
    TestAppDlgProc);

/* основное окно закрыто - завершаем приложение */
  return(FALSE);
}

/* функция настройки уведомляющей области */
BOOL CALLBACK TestAppDlgProc(HWND hDlg, 
                             UINT uMsg, 
                             WPARAM wParam, 
                             LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_INITDIALOG:
      /* инициализация окна диалога */
      TrayMessage(hDlg, NIM_ADD, NULL, NULL);
      StateChange(hDlg);
      break;

    case WM_DESTROY:
      /* разрушение окна диалога */
      TrayMessage(hDlg, NIM_DELETE, NULL, NULL);
      break;

    case WM_COMMAND:
      /* обработка сообщений от элементов окна диалога */
      switch (GET_WM_COMMAND_ID(wParam, lParam))
      {
        case IDCANCEL:
          EndDialog(hDlg, TRUE);
          break;

        case IDHIDE:
          ShowWindow(hDlg, SW_HIDE);
          break;
      }
      break;

    case WM_NOTIFYICON:
      /* обработка сообщений от пиктограммы 
         области уведомления */
      switch (lParam)
      {
        case WM_LBUTTONDOWN:
          switch (wParam)
          {
            case IDC_NOTIFY:
              /* смена состояния с заменой пиктограммы */
              g_uState = !g_uState;
              StateChange(hDlg);
              break;

            default:
              break;
          }
          break;

        case WM_RBUTTONDOWN:
          /* активизация окна диалога */
          ShowWindow(hDlg, SW_SHOW);
          SetForegroundWindow(hDlg); 
          break;

        default:
          break;
      }
      break;

    default:
      return(FALSE);
  }

  return(TRUE);
}

BOOL TrayMessage(HWND hDlg, 
                 DWORD dwMessage, 
                 HICON hIcon, 
                 PSTR pszTip)
{
  BOOL retCode;
  NOTIFYICONDATA tnd;

  /* формирование структуры для работы с областью уведомления */
  tnd.cbSize = sizeof(NOTIFYICONDATA);
  tnd.hWnd = hDlg;
  tnd.uID = IDC_NOTIFY;

  tnd.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
  tnd.uCallbackMessage = WM_NOTIFYICON;
  tnd.hIcon = hIcon;

  if (pszTip)
    lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
  else
    tnd.szTip[0] = '\0';

  /* собственно настройка области уведомления */
  retCode = Shell_NotifyIcon(dwMessage, &tnd);

  if (hIcon)
    DestroyIcon(hIcon);

  return retCode;
}

void StateChange(HWND hDlg)
{
  LPCSTR pszIDIcon;
  char szTip[64];

  /* в зависимости от текущего состояние загрузка
     нужного текста и пиктограммы */
  if (!LoadString(g_hinst, g_uState == 0 ? 
      IDC_STATE1 : IDC_STATE2, szTip, sizeof(szTip)))
    *szTip = '\0';

  pszIDIcon = MAKEINTRESOURCE(
    g_uState ? IDI_STATE1 : IDI_STATE2);

  TrayMessage(hDlg, NIM_MODIFY,
    LoadImage(g_hinst, pszIDIcon, IMAGE_ICON, 16, 16, 0),       
    szTip);
}
