#undef UNICODE
#pragma warning (disable:4996)
#define FILTER(ch)  (ch >= 'а' && ch <= 'я' || ch >= 'А' &&ch <= 'Я')
#define ESC_OF "Отказ от выбора или ошибка выполнения функции "
#include <windows.h>
#include <fstream>
#include <windowsx.h>
#include <iostream>
#include <string>
#include <vector>
#include "kWnd.h"
#include <commdlg.h>
#include <commdlg.inl>

using namespace std;

#include "Resource.h"
#define N1 21
#define N2 81
#define TOTAL_SIZE (3 * N1 + N2)

fstream fdat;
static OPENFILENAME ofn;

struct SubStr 
{
	char name[N1];
	char phone[N1];
	char birthday[N1];
	char address[N2];
};

union Data 
{
	SubStr ss;
	char line[TOTAL_SIZE];
};

class Listltem
{
	char buf[TOTAL_SIZE];
public:
	Listltem() { Clear(); }
	void Clear() { memset(dat.line, ' ', TOTAL_SIZE); }
	void DoOneString()
	{
		int count(0);
		for (int i(TOTAL_SIZE - 1); i > 0; --i)
			if (!dat.line[i])
				if (!count)
					count++;
				else dat.line[i] = ' ';
	}
	const char* GetBirthday()
	{
		memcpy(buf, dat.ss.birthday, N1);
		buf[N1 - 1] = 0;
		return buf;
	}
	const char* GetAddress()
	{
		memcpy(buf, dat.ss.address, N2);
		buf[N2 - 1] = 0;
		return buf;
	}
	Data dat;
};

Listltem item;

int fontHeight[] = { 16, 20, 24, 28, 30 };
int iFont = 0; 

BOOL CALLBACK ViewDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AddRecDiaProc(HWND, UINT, WPARAM, LPARAM);
void AdjustDialogSize(HWND hDlg);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Diag(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,
	LPSTR IpCmdLine, int nCmdShow)
{
	MSG msg;
	kWnd mainWndC("Телефонная книжка", hinstance, nCmdShow, WndProc,
		MAKEINTRESOURCE(IDR_MENU1), 100, 100, 400, 300);
	char szDirect[255];
	char szFileName[260] = "";
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szDirect;
	*(ofn.lpstrFile) = 0;
	ofn.nMaxFile = sizeof(szDirect);
	ofn.lpstrFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileName;
	*(ofn.lpstrFileTitle) = 0;
	ofn.nMaxFileTitle = sizeof(szFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

int fsize = 14;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	BOOL success;
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_32771: 
			GetOpenFileName(&ofn);
			break;
		case ID_32773: 
			PostQuitMessage(0);
			break;
		case ID_32772: 
			MessageBox(hWnd, "Для сохранения перейдите в Просмотр и нажмите ОК.\nТелефонна книга будет сохранена в первоначальный файл.", "Инструкция", MB_OK);
			break;
		case IDM_VIEW:
			hInst = GetModuleHandle(NULL);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEW), hWnd, ViewDlgProc);
			break;
		case IDM_DIAG:
			if (IDYES== MessageBox(hWnd, "Перед построением диаграммы необходимо перейти в Просмотр и нажать ОК.\nВ противном случае данные диаграммы могут быть некорректны.\nВы сохранили данные?", "Инструкция", MB_YESNO));
			{
				hInst = GetModuleHandle(NULL);
			    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIAG), hWnd, Diag);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void AdjustDialogSize(HWND hDlg)
{
	int nCtrlId[] = { IDC_GROUP_1, IDC_STATIC_ADDR, IDC_STATIC_BDAY,
	IDC_INFO_ADDR, IDC_INFO_BDAY, IDOK, IDCANCEL, IDC_REC_ADD,
	IDC_REC_DELETE };
	HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
	static LOGFONT lf;
	static HFONT hFontl;
	HDC hDC;
	TEXTMETRIC tm;
	int showTextWidth; 
	RECT rcLB; 
	int shift; 
	if (hFontl)
		DeleteObject(hFontl);
	lf.lfHeight = fontHeight[iFont];
	lstrcpy((LPSTR)&lf.lfFaceName, "Courier");
	hFontl = CreateFontIndirect(&lf);
	SendMessage(hListBox, WM_SETFONT, (WPARAM)hFontl, TRUE);
	hDC = GetDC(hListBox);
	SelectObject(hDC, hFontl);
	GetTextMetrics(hDC, &tm);
	ReleaseDC(hListBox, hDC);
	GetWindowRect(hListBox, &rcLB);
	showTextWidth = tm.tmAveCharWidth * 2 * N1;
	shift = showTextWidth - (rcLB.right - rcLB.left);
	ShiftWindow(hDlg, 0, 0, shift);
	ShiftWindow(IDC_LIST1, hDlg, 0, 0, shift);
	ShiftWindow(IDC_GROUP_0, hDlg, 0, 0, shift);
	for (int i = 0; i < sizeof(nCtrlId) / sizeof(int); ++i)
		ShiftWindow(nCtrlId[i], hDlg, shift);
	ShiftWindow(IDC_STATIC_PHONE, hDlg, shift / 2);
}

CHOOSECOLOR userColor;
CHOOSEFONT userFont;
static LOGFONT lf;
static DWORD rgbCurrent;
static COLORREF acrCustClr[16];
HFONT hFont;
HBRUSH Brush;
BOOL CALLBACK Diag(HWND hDiag, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc = GetDC(hDiag);
	PAINTSTRUCT ps;

	userFont.lpLogFont = &lf;
	int nAll(0), nMts(0), nLife(0), nA1(0), nOther(0);
	char Number[N1];
	char oper[20];
	Number[20] = '\0';

	fdat.open(ofn.lpstrFile, ios::in);
	if (!fdat) 
	{ 
		fdat.clear(); 
		return TRUE;
	}
	else 
		while (1) 
		{
		fdat.getline(item.dat.line, sizeof(Data));
		if (fdat.eof()) 
		{
			fdat.clear();
			break;
		}
		for (int i = 0; i < 20; i++)
			Number[i] = item.dat.line[i + 21];
		nAll++;
		if (Number[4] == '4')
			nA1++;
		else
			if (Number[4] == '3')
				nMts++;
			else
				if (Number[4] == '2')
				{
					if (Number[5] == '5')
						nLife++;
					else
						if (Number[5] == '9')
						{
							char t = Number[6];

							if (t == '1' || t == '3' || t == '6' || t == '9')
								nA1++;
							else
								if (t == '2' || t == '5' || t == '7' || t == '8')
									nMts++;

						}
				}
				else 
					nOther++;
	}
	fdat.close();

	switch (uMsg) {
	case WM_INITDIALOG:
		return FALSE;
	case WM_PAINT:
		hdc = BeginPaint(hDiag, &ps);
		Brush = CreateSolidBrush(userColor.rgbResult);

		SelectObject(hdc, Brush);
		SelectObject(hdc, hFont);
		Rectangle(hdc, 30, 150, 70, 150 - 140 * nA1 / nAll);
		Rectangle(hdc, 80, 150, 120, 150 - 140 * nMts / nAll);
		Rectangle(hdc, 130, 150, 170, 150 - 140 * nLife / nAll);
		Rectangle(hdc, 180, 150, 220, 150 - 140 * nOther / nAll);
		Rectangle(hdc, 230, 150, 270, 10);

		sprintf(oper, "%d", nA1);
		TextOut(hdc, 35, 220, oper, strlen(oper));
		TextOut(hdc, 30, 180, "A1", 6);

		sprintf(oper, "%d", nMts);
		TextOut(hdc, 85, 220, oper, strlen(oper));
		TextOut(hdc, 85, 180, "MTS", 3);

		sprintf(oper, "%d", nLife);
		TextOut(hdc, 135, 220, oper, strlen(oper));
		TextOut(hdc, 135, 180, "LIFE", 4);

		sprintf(oper, "%d", nOther);
		TextOut(hdc, 185, 220, oper, strlen(oper));
		TextOut(hdc, 185, 180, "Др.", 7);

		sprintf(oper, "%d", nAll);
		TextOut(hdc, 225, 220, oper, strlen(oper));
		TextOut(hdc, 225, 180, "Все", 3);

		EndPaint(hDiag, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDFONT:
			ZeroMemory(&userFont, sizeof(userFont));
			userFont.lStructSize = sizeof(userFont);
			userFont.hwndOwner = hDiag;
			userFont.lpLogFont = &lf;
			userFont.rgbColors = rgbCurrent;
			userFont.Flags = CF_SCREENFONTS | CF_EFFECTS;
			ChooseFont(&userFont);
			hFont = CreateFontIndirect(&lf);
			InvalidateRect(hDiag, NULL, false);
			SelectObject(hdc, hFont);
			SetTextColor(hdc, userFont.rgbColors);
			InvalidateRect(hDiag, NULL, false);
			break;
		case IDOK:
			ZeroMemory(&userColor, sizeof(CHOOSECOLOR));
			userColor.lStructSize = sizeof(CHOOSECOLOR);
			userColor.hwndOwner = hDiag;
			userColor.lpCustColors = (LPDWORD)acrCustClr;
			userColor.rgbResult = rgbCurrent;
			ChooseColor(&userColor);
			InvalidateRect(hDiag, NULL, false);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDiag, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK ViewDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	static HWND hEditInfoAddr, hEditInfoBday;
	HWND hCtrl;
	COLORREF editInfoColor;
	static HBRUSH hBrush; 
	int iCurItem; 
	BOOL dlgYes;
	int i;
	char buf[10];
	editInfoColor = RGB(190, 255, 255);
	int nItems;
	static HWND hListBox, hComboFont;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		hListBox = GetDlgItem(hDlg, IDC_LIST1);
		hComboFont = GetDlgItem(hDlg, IDC_FONT);
		hEditInfoAddr = GetDlgItem(hDlg, IDC_INFO_ADDR);
		hEditInfoBday = GetDlgItem(hDlg, IDC_INFO_BDAY);

		hBrush = CreateSolidBrush(editInfoColor);

		AdjustDialogSize(hDlg);

		for (i = 0; i < sizeof(fontHeight) / sizeof(int); ++i) 
		{
			sprintf(buf, "%d", fontHeight[i]);
			SendMessage(hComboFont, CB_ADDSTRING, 0, (LPARAM)buf);
		}
		SendDlgItemMessage(hDlg, IDC_FONT, CB_SETCURSEL, iFont, 0);

		fdat.open(ofn.lpstrFile, ios::in);
		if (!fdat)
		{
			fdat.clear();
			return TRUE;
		}
		else
			while (1)
			{
				fdat.getline(item.dat.line, sizeof(Data));
				if (fdat.eof())
				{
					fdat.clear();
					break;
				}
				SendMessage(hListBox, LB_ADDSTRING, 0,
					(LPARAM)item.dat.line);
			}
		fdat.close();
		return TRUE;

	case WM_CTLCOLORSTATIC:
		hCtrl = (HWND)lParam;
		if ((hCtrl == hEditInfoAddr) || (hCtrl == hEditInfoBday))
		{
			SetBkColor((HDC)wParam, editInfoColor);
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (DWORD)hBrush;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			fdat.open(ofn.lpstrFile, ios::out | ios::trunc);
			if (!fdat) {
				MessageBox(hDlg, "Ошибка открытия файла", "Ошибка", MB_OK);
				return FALSE;
			}
			nItems = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < nItems; ++i) {
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)item.dat.line);
				fdat << item.dat.line << endl;
			}
			fdat.close();
			char strn[3];
			if (strcmp(strn, "14") == 0) fsize = 14;
			else if (strcmp(strn, "15") == 0) fsize = 15;
			else fsize = 16;
			EndDialog(hDlg, TRUE);
			return TRUE;
			break;
		case IDC_REC_ADD:
			dlgYes = DialogBox((HINSTANCE)GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDD_ADD_REC), hDlg, AddRecDiaProc);
			if (dlgYes)
				SendMessage(hListBox, LB_ADDSTRING, 0,
					(LPARAM)item.dat.line);
			break;
		case IDC_REC_DELETE:
			iCurItem = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (iCurItem != LB_ERR)
			{
				SendMessage(hListBox, LB_DELETESTRING, iCurItem, 0);
				SetDlgItemText(hDlg, IDC_INFO_ADDR, "");
				SetDlgItemText(hDlg, IDC_INFO_BDAY, "");
			}
			else
			{
				MessageBox(hDlg, "Сначала надо выделить элемент списка",
					"Ошибка", MB_OK);
				break;
			}
			break;
		case IDC_LIST1:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				iCurItem = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_GETTEXT, iCurItem,
					(LPARAM)item.dat.line);
				SetDlgItemText(hDlg, IDC_INFO_ADDR, item.GetAddress());
				SetDlgItemText(hDlg, IDC_INFO_BDAY, item.GetBirthday());
				return TRUE;
			}
			break;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		case IDC_FONT:
			switch (HIWORD(wParam)) 
			{
			case CBN_SELCHANGE:
				iFont = SendMessage(hComboFont, CB_GETCURSEL, 0, 0);
				AdjustDialogSize(hDlg);
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK AddRecDiaProc(HWND hDlg, UINT uMsg,
	WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_INPUT_NAME));
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			item.Clear();
			GetDlgItemText(hDlg, IDC_INPUT_NAME, item.dat.ss.name, N1);
			GetDlgItemText(hDlg, IDC_INPUT_PHONE, item.dat.ss.phone, N1);
			GetDlgItemText(hDlg, IDC_INPUT_BDAY, item.dat.ss.birthday, N1);
			GetDlgItemText(hDlg, IDC_INPUT_ADDR, item.dat.ss.address, N2);
			item.DoOneString();
			EndDialog(hDlg, TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
