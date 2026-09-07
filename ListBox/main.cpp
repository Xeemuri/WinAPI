#include <Windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* g_szVALUES[] = { "This", "is", "my", "First", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	switch (uMSG)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		for (int i = 0; i < sizeof(g_szVALUES) / sizeof(g_szVALUES[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_szVALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //get current selection
			CHAR sz_buffer[256] = {};
			SendMessage(hListBox, LB_GETTEXT, i, (WPARAM)sz_buffer);
			CHAR sz_message[256] = {};
			sprintf(sz_message, "Вы выбрали вариант №%i со значением %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Выбранный элемент", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		case IDC_BUTTON_ADD:
		{
			CHAR sz_buffer[256] = {};
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			break;
		}
		case IDC_BUTTON_DELETE:
		{
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
			break;
		}
		case IDC_LIST_BOX:
		{
			if (HIWORD(wParam) == DOUBLE_CLICK)
			{
				MessageBox(hListBox, "Вы дважды нажали на элемент", "", MB_OK | MB_ICONINFORMATION);
			}
			break;
		}
		}
	}
	break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}