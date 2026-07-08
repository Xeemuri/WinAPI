#include <Windows.h>
#include "resource.h"
#include <time.h>

CONST CHAR g_sz_INVITE[] = "Введите имя пользователя";

//Прототип функции:
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, NULL);
}
//Рализация функции:
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Отрабатывает при запуске окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);

	}
	break;
	case WM_COMMAND:	//Обработка кнопок, действий мышью и т.д.
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		CONST INT SIZE = 256;
		CHAR szBuffer[SIZE] = {};
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(szBuffer, g_sz_INVITE) == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(szBuffer, "") == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
			break;
		case IDC_BUTTON_COPY:
		{
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК!", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	
	return FALSE;
}