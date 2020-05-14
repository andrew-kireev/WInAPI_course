// last_lab.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "last_lab.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


#define MAX_LOADSTRING 100
#define PATH L"C:\\Users\\User\\source\\repos\\last_lab\\last_lab\\test.txt"


#pragma warning(disable : 4996)

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
	std::vector<std::string> data;
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LASTLAB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LASTLAB));

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
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LASTLAB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LASTLAB);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   HMENU WINAPI a;
   HMENU Menu = CreateMenu();
   HMENU hPopupMenu1 = CreatePopupMenu();
   HMENU hPopupMenu2 = CreatePopupMenu();
   AppendMenu(Menu, MF_STRING | MF_POPUP, (UINT)hPopupMenu1, L"&Включить");
   {
	   AppendMenu(hPopupMenu1, MF_STRING, 100, L"Включить загрузку данных");
	   AppendMenu(hPopupMenu1, MF_STRING, 200, L"Включить отрисовку");
   }
   AppendMenu(Menu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Выключить");
   {
	   AppendMenu(hPopupMenu2, MF_STRING, 300, L"Выключить загрузку");
	   AppendMenu(hPopupMenu2, MF_STRING, 400, L"Выключить отрисовку");
   }
   SetMenu(hWnd, Menu);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);

int a = 0;
BOOL thread1_working = false;
BOOL thread2_working = false;


LPWSTR convertStr(LPCSTR pInStr)
{
	int length = strlen(pInStr);
	wchar_t * pwstr = new wchar_t[length];
	int result = MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, pInStr, length,
		pwstr, length
	);
	pwstr[length] = L'\0';
	return LPWSTR(pwstr);
}

std::map<int, int> names = { {7, 8},  {3, 7}, {2, 7}, {1, 8},
							{4, 7}, {5, 13}, {6, 9} };

const TCHAR szCounterFileName[] = L"C:\\Users\\User\\source\\repos\\last_lab\\last_lab\\list.txt";
const TCHAR szCheckOk[] = L"Все в порядке, продолжайте работу";

DWORD WINAPI Thread1(LPVOID t)
{
	//std::vector<std::string> data;
	//std::wstring buffer;
	//buffer.resize(3000);
	OVERLAPPED olf = { 0 };
	LARGE_INTEGER li = { 0 };
	li.QuadPart = 1;
	olf.Offset = li.LowPart;
	olf.OffsetHigh = li.HighPart;

	LPSTR buffer = (CHAR*)calloc(300, sizeof(CHAR));
	DWORD iNumread = 0;

	DWORD dwCounter, dwTemp;
	HANDLE hFile = CreateFile(PATH, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (!ReadFile(hFile, buffer, 300, &iNumread, &olf)) {
		return 1;
	}

	int i = 1;
	int k = 0;

	std::string data = buffer;
	
	while (thread1_working) {

		
		RECT rect;
		PAINTSTRUCT ps;
		GetClientRect(HWND(t), &rect);
		std::cout << "p" << std::endl;
		//_stprintf(buff, TEXT("Height: %d Width: %d"), 0, 0);

		LPCWSTR new_buf = convertStr(buffer);

		
		
		HDC hdc = GetDC(HWND(t));
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
		Rectangle(hdc, 50, 50, 400, 305);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOut(hdc, 280, 100, new_buf + k, names[i]);
		EndPaint(HWND(t), &ps);
		Sleep(1000);
		k += names[i];
		++i;
		if (i == 8) {
			i = 1;
			k = 0;
		}

		/*for (auto i : data) {
			HDC hdc = GetDC(HWND(t));
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 280, 100, reinterpret_cast<const wchar_t*>(i.c_str), i.size());
			EndPaint(HWND(t), &ps);
			Sleep(1000);
		}  */
	}
	
	return 0;
}


DWORD WINAPI Thread2(LPVOID t)
{
	bool left_side = true;

	while (thread2_working) {
	
		RECT rect;
		PAINTSTRUCT ps;
		GetWindowRect(HWND(t), &rect);
		int width = (int)(rect.right - rect.left);
		int height = (int)(rect.bottom - rect.top);
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(rand() % 255, rand() % 255, rand() % 255));

		if (left_side) {
			
			::MoveToEx(hdc, 250, 400, NULL);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 150, 350, NULL);
			::LineTo(hdc, 350, 450);
			Sleep(1000);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(255, 255, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
			Rectangle(hdc, 150, 450, 350, 350);
			ReleaseDC(HWND(t), hdc);
	
			::SelectObject(hdc, (HGDIOBJ)hBrush);
			::DeleteObject(hBrush);
			left_side = false;

	
		}
		else {

	
			::MoveToEx(hdc, 250, 400, NULL);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 350, 350, NULL);
			::LineTo(hdc, 150, 450);
			Sleep(1000);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(255, 255, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
			Rectangle(hdc, 150, 450, 350, 350);
			ReleaseDC(HWND(t), hdc);
			left_side = true;
		}
	}
	return 0;
}



//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::cout << "00000" << std::endl;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case 100:
			{
				thread1_working = true;
				std::cout << "pppp" << std::endl;
				hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
				break;

			}
			case 200:
			{
				thread2_working = true;
				hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);

				break;
			}
			case 300:
			{
			
				TerminateThread(hThread1, 0);
				thread1_working = false;
				break;
			}
			case 400:
			{
				TerminateThread(hThread2, 0);
				thread2_working = false;
				break;

			}
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }

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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
