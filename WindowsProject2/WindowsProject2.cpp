﻿#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// WindowsProject2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100
using namespace std;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

SystemManager& manager = SystemManager::getInstance(); // 레퍼런스로 싱글톤
Math& calculator = Math::getInstance(); // 포인터로 싱글톤
RECT rectView;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUPWINDOW,
		1200, 300, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#define timer_1 11
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT cur_point;

	TCHAR info1[100]; // 마우스 위치

	switch (message)
	{
	case WM_CREATE:
	{
		manager.setCannon();
		cur_point.x = 0;
		cur_point.y = 0;

		GetClientRect(hWnd, &rectView);
		SetTimer(hWnd, timer_1, 30, NULL);

		break;
	}
	case WM_TIMER:
	{
		for (int i = 0; i < manager.getObj().size(); i++)
		{
			manager.getObj()[i]->Update(rectView);
		}
		manager.getCannon()->Update(cur_point);
		manager.ObjectDelete();

		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		cur_point.x = LOWORD(lParam);
		cur_point.y = HIWORD(lParam);
		manager.ObjectNew(CANNONBALL);

		InvalidateRgn(hWnd, NULL, FALSE);

		break;
	}
	case WM_MOUSEMOVE:
	{
		cur_point.x = LOWORD(lParam);
		cur_point.y = HIWORD(lParam);

		wsprintf(info1, TEXT("%d , %d"), cur_point.x, cur_point.y);
		hdc = GetDC(hWnd);
		TextOut(hdc, 0, 0, info1, _tcslen(info1));
		ReleaseDC(hWnd, hdc);

		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rectView);
		HDC MemDC1 = GetDC(hWnd);
		HDC MemDC2 = CreateCompatibleDC(MemDC1);
		HBITMAP BackBit1 = CreateCompatibleBitmap(MemDC1, rectView.right, rectView.bottom);
		HBITMAP BackBit2 = (HBITMAP)SelectObject(MemDC2, BackBit1);
		FillRect(MemDC2, &rectView, (HBRUSH)GetSysColor(COLOR_BACKGROUND));
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		for (int i = 0; i < manager.getObj().size(); i++)
		{
			manager.getObj()[i]->Draw(MemDC2);
		}
		manager.getCannon()->Draw(MemDC2);

		// 여기까지 ~~
		BitBlt(MemDC1, 0, 0, rectView.right, rectView.bottom, MemDC2, 0, 0, SRCCOPY);
		SelectObject(MemDC2, BackBit2);
		DeleteDC(MemDC2);
		DeleteObject(BackBit1);
		ReleaseDC(hWnd, hdc);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		delete manager.getCannon();
		for (int i = 0; i < manager.getObj().size(); i++)
		{
			delete manager.getObj()[i];
		}
		KillTimer(hWnd, timer_1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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