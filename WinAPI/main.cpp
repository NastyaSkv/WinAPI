#include<Windows.h>
#include"resource.h"


CONST CHAR gsz_LOGIN_INVITATION[] = "Введите имя пользователя";
CONST CHAR gsz_PASSWORD_INVITATION[] = "Введите пароль";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//#define MSG_BOX

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MSG_BOX
	MessageBox(
		NULL,   //родительское окно
		"Привет! Это наше первое сообщение",
		"Заголовок окна сообщения",
		MB_YESNOCANCEL | MB_HELP    //набор кнопок
		| MB_ICONASTERISK           //значок
		| MB_DEFBUTTON3             //кнопка по умолчанию
		| MB_SYSTEMMODAL            //WS_EX_TOPMOST -  поверх всех окон     
	);
#endif // MSG_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DLGPROC(DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:   //создание элементов окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		//Получаем обработчики окна текстовых полей
		//  HWND - Hander to Window (обработчик окна)
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

		//Для того чтобы установить текст в окна hEditLogin и hEditPassword,
		//нужно отправить сообщение этим окнам
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)gsz_LOGIN_INVITATION);
		SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)gsz_PASSWORD_INVITATION);
	}
	break;

	case WM_COMMAND:      //обработка команд нажатия кнопок
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, gsz_LOGIN_INVITATION) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				//SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strlen(sz_buffer) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)gsz_LOGIN_INVITATION);
			}
		}
			break;
		case IDC_BUTTON_COPY:
		{
			//Создаем буфер, через который будет производиться копирование
			CONST INT SIZE = 256;
			CHAR buffer[SIZE] = {};
			//Получаем окна тактовых полей, для того, чтобы им можно было отправлять сообщения
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//Читаем содержимое тактового поля LOGIN:
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)buffer);
			//Загружаем текст из буфера в поле PASSWORD:
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)buffer);
		}
		break;

		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;

		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:        //закрытие окна
		EndDialog(hwnd, 0);
	}
	return FALSE;
}