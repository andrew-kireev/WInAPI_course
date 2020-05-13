// last_lab.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "last_lab.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#define MAX_LOADSTRING 100


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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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





DWORD WINAPI Thread1(LPVOID t)
{
	std::vector<std::string> data;
	
	/*
	std::string line;
	std::fstream in;
	in.open("C:\\Users\\User\\OneDrive\\Рабочий стол\\Вывод - Сборка.txt");
	//std::fstream in("C:\\Users\\User\\OneDrive\\Рабочий стол\\Вывод - Сборка.txt");
	std::fstream out("C:\\Users\\User\\source\\repos\\last_lab\\last_lab\\test.txt‪");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			data.push_back(line);
		}
	}
	in << "зашел";
	in.close();
	for (auto i : data) {
		out << i;
	}
	out.close();   */

	for (int i = 0; i < 10; ++i) {
		data.push_back(std::to_string(i));

	}

	while (thread1_working) {

	

		RECT rect;
		PAINTSTRUCT ps;
		TCHAR szT[30];
		TCHAR buff[300];
		GetClientRect(HWND(t), &rect);
		std::cout << "p" << std::endl;
		//_stprintf(buff, TEXT("Height: %d Width: %d"), 0, 0);
		for (auto i : data) {
			std::cout << i << std::endl;
			HDC hdc = GetDC(HWND(t));
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 200, 200, reinterpret_cast<const wchar_t*>(i.c_str()), i.size());
			EndPaint(HWND(t), &ps);
			//Sleep(60);
		} 
	}
	
	return 0;
}


DWORD WINAPI Thread2(LPVOID t)
{
	while (thread2_working) {
		RECT rect;
		PAINTSTRUCT ps;
		GetWindowRect(HWND(t), &rect);
		HDC hdc = GetDC(HWND(t));
		hdc = BeginPaint(hWnd, &ps);
		HPEN pen = ::CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		GetClientRect(hWnd, &rect);
		void* oldPen = ::SelectObject(hdc, pen);
		::MoveToEx(hdc, 0, 0, NULL);
		::LineTo(hdc, 200, 175);
		EndPaint(hWnd, &ps);
		::SelectObject(hdc, (HGDIOBJ)oldPen);
		::DeleteObject(pen);
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
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
