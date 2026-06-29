#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MessageBox
	(
		NULL, //Родительское окно
		"Hello WinAPI!\nРазработка настольных приложений для Windows. ", //Сообщение, выводимое пользователюз
		"Hello", //Заголовок окна
		MB_YESNOCANCEL | MB_HELP | MB_ICONASTERISK | MB_DEFBUTTON3 | MB_SYSTEMMODAL//Флаги, которые определяют значок, выводимый в окне, набор кнопок и некоторые дополнительные параметры
	);

}