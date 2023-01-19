#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>

#define IDC_BUTTON_0    1000
#define IDC_BUTTON_1    1001
#define IDC_BUTTON_2    1002
#define IDC_BUTTON_3    1003
#define IDC_BUTTON_4    1004
#define IDC_BUTTON_5    1005
#define IDC_BUTTON_6    1006
#define IDC_BUTTON_7    1007
#define IDC_BUTTON_8    1008
#define IDC_BUTTON_9    1009

#define IDC_BUTTON_PLUS  1010
#define IDC_BUTTON_MINUS 1011
#define IDC_BUTTON_ASTER 1012
#define IDC_BUTTON_SLASH 1013
#define IDC_BUTTON_POINT 1014
#define IDC_BUTTON_EQUAL 1015
#define IDC_BUTTON_CLEAR 1016
#define IDC_EDIT         1017

CONST INT g_INTERVAL = 10;
CONST INT g_BUTTON_SIZE = 50;
CONST INT g_DISPLAY_WIDTH = 400;
CONST INT g_DISPLAY_HEIGHT = 20;
CONST INT g_START_X = 10;
CONST INT g_START_Y = 10;


CONST CHAR gsz_MY_WINDOW_CLASS[] = "MyWindowClass";
CONST CHAR gsz_WINDOW_NAME[] = "My First Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, "fire.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "fruit.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = (HICON)LoadCursorFromFile("pumpkin.cur");
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = gsz_MY_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * 3 / 4;
	int window_height = screen_height * 3 / 4;
	int start_x = screen_width / 8;
	int start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,    //ExStyle
		gsz_MY_WINDOW_CLASS,           //Class name
		gsz_WINDOW_NAME,              //Widows name
		//WS_OVERLAPPEDWINDOW,           //dwStyle
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		start_x, start_y,  //Начальная позиция окна
		window_width, window_height,  //Размер окна
		NULL,       //HWND родительского окна. У главного окна НЕТ родительского окна
		NULL,       //Menu отсутствует
		hInstance,   //
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);  //Задает режим отображения окна (свернуто в окно, развернуто на весь экран)
	UpdateWindow(hwnd); //Прорисовывает содержимое окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//Создаем экран калькулятора:
		CreateWindowEx(NULL, "Edit", "",
			WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_RIGHT,
			10, 10,
			400, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		//Создаем кнопки:
		int digit = 1;
		char sz_digit[] = "0";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = '0' + digit;
				CreateWindowEx(
					NULL, "BUTTON", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * j,
					g_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL * 2 + (g_BUTTON_SIZE + g_INTERVAL) * (2 - i),
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_7,
					GetModuleHandle(NULL),
					NULL
				);
				digit++;
			}
		}
	}
		break;
	case WM_COMMAND:break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		sprintf(sz_buffer, "%s, Position:%dx%d, Size:%dx%d", gsz_WINDOW_NAME,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:
		/*switch
			(
				MessageBox(hwnd,
					"Вы действительно хотите закрыть окно?",
					"Вопрос на миллион долларов",
					MB_YESNO | MB_ICONQUESTION)
			)
		{
		case IDYES:
			MessageBox(hwnd, "Лучше бы дверь закрыли:)", "Полезная инфа", MB_OK | MB_ICONQUESTION);
			DestroyWindow(hwnd);
			break;
		}*/
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}