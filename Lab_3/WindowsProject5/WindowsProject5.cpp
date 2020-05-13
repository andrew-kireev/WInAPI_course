// WindowsProject5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject5.h"
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define MAX_LOADSTRING 100
#define ID_FILE_NEW    32782





// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hWnd;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInst;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

/*
hwndMain = CreateWindowEx(0,
	szWindowClass,
	_T("Крестики-нолики"),
	WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	366,
	382,
	NULL,
	NULL,
	hInst,
	NULL); */
//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 600, 570, NULL, NULL, hInstance, NULL);// Установили параметры размещения дочерних оконо 600/570

	if (!hWnd)
	{
		return FALSE;
	}
	
	
	HMENU hmenu1;
	hmenu1 = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Файл");
	{
		AppendMenu(hPopupMenu, MF_STRING, 100, L"Новый");
		AppendMenu(hPopupMenu, MF_STRING, 200, L"Выход");
	}
	SetMenu(hWnd, hmenu1);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
TCHAR ChildClassName[MAX_LOADSTRING] = _T("WinChild");
ATOM MyRegisterChildClass()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = ChildProc;
	wcex.hInstance = hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszClassName = ChildClassName;
	return RegisterClassEx(&wcex);
}

static HWND hChild[9];
unsigned char k[9] = { 0 };
unsigned char k_[9] = { 0 };




/*((k[1] == 1 &&  k[2] == 1 &&  k[3] == 1) || (k[4] == 1 && k[5] == 1 && k[6] == 1) || (k[7] == 1 &&  k[8] == 1 && k[9] == 1) ||
		(k[1] == 1 && k[4] == 1 && k[7] == 1) || (k[2] == 1 && k[5] == 1 && k[8] == 1) || (k[3] == 1 && k[6] == 1 && k[9] == 1)
		|| (k[1] == 1 && k[5] == 1 && k[9] == 1) || (k[3] == 1 && k[5] == 1 && k[7] == 1))*/


bool full_field() {
	if ((k[0] == 1 || k_[0] == 1) && (k[1] == 1 || k_[1] == 1) && (k[2] == 1 || k_[2] == 1) &&
		(k[3] == 1 || k_[3] == 1) && (k[4] == 1 || k_[4] == 1) && (k[5] == 1 || k_[5] == 1) &&
		(k[6] == 1 || k_[6] == 1) && (k[7] == 1 || k_[7] == 1) && (k[8] == 1 || k_[8] == 1))
		return true;
	return false;
}

void Check() {
	bool round_won = false;
	if (((k[0] == 1 && k[1] == 1 && k[2] == 1) || (k[3] == 1 && k[4] == 1 && k[5] == 1) || (k[6] == 1 && k[7] == 1 && k[8] == 1) ||
		(k[0] == 1 && k[3] == 1 && k[6] == 1) || (k[1] == 1 && k[4] == 1 && k[7] == 1) || (k[2] == 1 && k[5] == 1 && k[8] == 1)
		|| (k[0] == 1 && k[4] == 1 && k[8] == 1) || (k[2] == 1 && k[4] == 1 && k[6] == 1))) {
		round_won = true;
		MessageBox(hWnd, _T("Победил игрок 1"), _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
	}
	else if (((k_[0] == 1 && k_[1] == 1 && k_[2] == 1) || (k_[3] == 1 && k_[4] == 1 && k_[5] == 1) || (k_[6] == 1 && k_[7] == 1 && k_[8] == 1) ||
		(k_[0] == 1 && k_[3] == 1 && k_[6] == 1) || (k_[1] == 1 && k_[4] == 1 && k_[7] == 1) || (k_[2] == 1 && k_[5] == 1 && k_[8] == 1)
		|| (k_[0] == 1 && k_[4] == 1 && k_[8] == 1) || (k_[2] == 1 && k_[4] == 1 && k_[6] == 1))) {
		round_won = true;
		MessageBox(hWnd, _T("Победил игрок 2"), _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
	}
	else if (full_field()) {
		MessageBox(hWnd, _T("Ничья"), _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
	}
}





void ResetGame()
{
	RECT rect;
	for (int i = 0; i < 9; i++) {
		k[i] = 0;
		k_[i] = 0;
		::GetClientRect(hChild[i], &rect);
		::InvalidateRect(hChild[i], &rect, TRUE);
	}
	
	::GetClientRect(hWnd, &rect);
	::InvalidateRect(hWnd, &rect, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;
	static int sx, sy;
	switch (message)
	{
	case WM_CREATE:
		MyRegisterChildClass();
		for (i = 0; i < 9; i++)
			hChild[i] = CreateWindow(ChildClassName, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		// Вданной функций мы создали Индексы и 9 дочерних окон
		// Дочерние окна это наши квадратики на форме 
		//hChild - Общая функция для всех 9 дочерних окон
		// [i] - Индекс по которым мы различаем наши 9 дочерних окон
		break;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			break;//Кнопка свертвывания окна
		sx = LOWORD(lParam) / 3; // ширина дочернего окна
		sy = HIWORD(lParam) / 3; //Высота дочернего окна
		for (i = 0; i < 9; i++)
		{
			MoveWindow(hChild[i], (i % 3)*sx, (i / 3)*sy, sx, sy, TRUE);
			UpdateWindow(hChild[i]);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			for (i = 0; i < 1; i++)
			{
				k[i] = 0;
				InvalidateRect(hChild[i], NULL, 1);
				UpdateWindow(hChild[i]);
			}
			break;
		case IDM_EXIT:DestroyWindow(hWnd);
			break;
		case 100:
			ResetGame();
			return 0;
		case 200:
			DestroyWindow(hWnd);
			break;
		default:return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool x_can_write = false;


////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HDC hdc;
	RECT rt;
	int i, s;	
	char *ch;
	static HBRUSH       g_brush[2];
	static int          g_brush_index = 0;
	g_brush[0] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	g_brush[1] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	switch (message)
	{
	case WM_LBUTTONDOWN:
		for (i = 0; hWnd != hChild[i]; i++);
		if (k[i] == 1 || k_[i] == 1)
			break;
		else if (k_[i] == 0 && x_can_write == false) {
			k[i] = 1;
			x_can_write = true;
		}
		InvalidateRect(hWnd, NULL, 1);
		UpdateWindow(hWnd);
		srand(lParam);
		Check();
		break;
		//*************************
	case WM_RBUTTONDOWN:
		//g_brush_index ^= 1;
		for (i = 0; hWnd != hChild[i]; i++);
		if (k[i] == 1 || k_[i] == 1)
			break;
		else if (k[i] == 0 && x_can_write == true){
			k_[i] = 1;
			x_can_write = false;
		}
		InvalidateRect(hWnd, NULL, 1);  // вызов функций окраски с пайнта
		UpdateWindow(hWnd);
		Check();
		break;
		//**********************
	case WM_PAINT:
		for (i = 0; hWnd != hChild[i]; i++);
		if (k[i])
		{
			hdc = BeginPaint(hWnd, &ps);
			HPEN pen = ::CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
			void* oldPen = ::SelectObject(hdc, pen);
			void* oldBr = ::SelectObject(hdc, GetStockObject(NULL_BRUSH));
			GetClientRect(hWnd, &rt);
			::Ellipse(hdc, 40, 135, 140, 35);

			EndPaint(hWnd, &ps);
			::SelectObject(hdc, (HGDIOBJ)oldBr);
			::SelectObject(hdc, (HGDIOBJ)oldPen);
			::DeleteObject(pen);
		}
		else if (k_[i]) {
	
			hdc = BeginPaint(hWnd, &ps);
			HPEN pen = ::CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
			GetClientRect(hWnd, &rt);
			void* oldPen = ::SelectObject(hdc, pen);
			
			//FillRect(ps.hdc, &ps.rcPaint, g_brush[g_brush_index]);//Функция FillRect заполняет прямоуголник кистью
		//  FillRect( ps.hdc, &ps.rcPaint, g_brush[1] );//Функция FillRect заполняет прямоуголник кистью
			::MoveToEx(hdc, 0, 0, NULL);
			::LineTo(hdc, 200, 175);
			::MoveToEx(hdc, 0, 163, NULL);
			::LineTo(hdc, 187, 0);
			EndPaint(hWnd, &ps);
			::SelectObject(hdc, (HGDIOBJ)oldPen);
			::DeleteObject(pen);
		}
	default:return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
