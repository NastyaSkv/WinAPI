#include<Windows.h>

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanse, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DLGPROC(DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:   //�������� ��������� ����
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:      //��������� ������ ������� ������
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			//������� �����, ����� ������� ����� ������������� �����������
			CONST INT SIZE = 256;
			CHAR buffer[SIZE] = {};
			//�������� ���� �������� �����, ��� ����, ����� �� ����� ���� ���������� ���������
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		}
		break;
		case IDOK:MessageBox(NULL, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:        //�������� ����
		EndDialog(hwnd, 0);
	}
	return FALSE;
}