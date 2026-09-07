#include <Windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* g_szVALUES[] = { "This", "is", "my", "First", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam);

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
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
			break;
		case IDOK:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //get current selection
			CHAR sz_buffer[256] = {};
			SendMessage(hListBox, LB_GETTEXT, i, (WPARAM)sz_buffer);
			CHAR sz_message[256] = {};
			sprintf(sz_message, "Вы выбрали вариант №%i со значением %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Выбранный элемент", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			SetFocus(GetDlgItem(hwnd, IDC_EDIT_ELEMENT));
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
			{
				CHAR sz_buffer[256] = {}; 
				HWND hEditElement = GetDlgItem(hwnd, IDC_EDIT_ELEMENT);
				SendMessage(hEditElement, WM_GETTEXT, 256, (LPARAM)sz_buffer);

				//здесь hwnd - это окно с вводом, так что нужно найти родителя чтоб 
				//отправить туда значения (чтобы вообще определить листбокс)
				HWND hParent = GetParent(hwnd);
				HWND hListBox = GetDlgItem(hParent, IDC_LIST_BOX);
				if (SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				else
				{
					MessageBox(hwnd, "Такой элемент уже есть в списке", "Info", MB_OK | MB_ICONINFORMATION);
					break;
				}
			}
			case IDCANCEL:
				EndDialog(hwnd, 0);
				break;
			}
			break;
		}
		case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}