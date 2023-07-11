//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

// WindowsProject2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

using namespace std;
using namespace Gdiplus;
ULONG_PTR g_GdiToken;

// 전역 변수:
int spawn_interval = 1000; // 장애물 생성 간격 1초 -> 0.1초

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

	Gdi_Init();

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	Gdi_End();
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
		500, 100, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

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
	static POINT cur_point;
	static int interval;
	static TCHAR str[100];
	static int state;

	HDC hdc;
	PAINTSTRUCT ps;

	static RECT rt;

	switch (message)
	{
	case WM_CREATE:
	{
		state = TRUE; // 게임 진행 상태, FALSE(0)되면 게임 종료
		interval = 3; // 장애물 생성 간격 조절 변수 (타이머 3번당 생성 간격 감소)
		cur_point.x = 0;
		cur_point.y = 0; // 마우스 좌표 초기화

		GetClientRect(hWnd, &rectView);

		/* 화면을 모니터 정중앙으로 */
		int screenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
		int screenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
		PlaceInCenterOfScreen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		rt = { screenWidth - WIDTH2 / 2, screenHeight - HEIGHT2 / 2, screenWidth + WIDTH2 / 2, screenHeight + HEIGHT2 / 2 };
		ClipCursor(&rt); // 마우스 커서 가두기

		/* 대포 동적할당 */
		manager.setCannon();

		/* 블럭 동적할당 */
		int block_number = WIDTH2 / (LENGTH * 2) + 1;
		int block_interval = (WIDTH2 % (LENGTH * 2)) / block_number;
		for (int i = 1; i < block_number - 1; i++)
		{
			manager.ObjectNew(BLOCK, i * LENGTH * 2 + block_interval, HEIGHT - LENGTH);
		}

		/* 타이머 설정 */
		SetTimer(hWnd, timer_1, 24, NULL);
		SetTimer(hWnd, timer_2, spawn_interval, SpawnObstacle); // 장애물 생성 간격 타이머 : 1000ms -> 100ms까지 줄어듬

		break;
	}
	case WM_TIMER:
	{
		if (wParam == timer_1 && state == TRUE)
		{
			if (manager.getLife() == 0)
			{
				state = FALSE;

				DialogBox(hInst, MAKEINTRESOURCE(IDD_DEAD), hWnd, DeadProc); // 다시? 아니면 종료?

				break;
			}

			/* 오브젝트 관리 매니저 */
			for (int i = 0; i < manager.getObj().size(); i++)
			{
				manager.getObj()[i]->Update(rectView);
			}
			manager.getCannon()->Update(cur_point);
			manager.ObjectDelete();

			/* 장애물 생성 간격 조절 */
			if (spawn_interval > 100)
			{
				interval--;
				if (interval == 0)
				{
					spawn_interval--;
					interval = 2;
				}
			}
			InvalidateRgn(hWnd, NULL, FALSE);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		ClipCursor(&rt); // 커서 가두기

		cur_point.x = LOWORD(lParam);
		cur_point.y = HIWORD(lParam);
		if (manager.getCannon()->CanItAttack() == true)
		{
			manager.ObjectNew(CANNONBALL);
		}

		break;
	}
	case WM_MOUSEMOVE:
	{
		cur_point.x = LOWORD(lParam);
		cur_point.y = HIWORD(lParam);
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

		HDC MemDC2 = CreateCompatibleDC(hdc);
		HBITMAP BackBit1 = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		HBITMAP BackBit2 = (HBITMAP)SelectObject(MemDC2, BackBit1);
		FillRect(MemDC2, &rectView, (HBRUSH)GetSysColor(COLOR_BACKGROUND));
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		wsprintf(str, TEXT("점수 : %d"), manager.getScore());
		TextOut(MemDC2, 100, 100, str, _tcslen(str));
		wsprintf(str, TEXT("남은 총알 : %d발"), 3 - manager.getCannonballNum());
		TextOut(MemDC2, 100, 120, str, _tcslen(str));

		wsprintf(str, TEXT("장애물 생성 간격 : %dms"), spawn_interval);
		Gdi_Draw(MemDC2, str);

		if (state == TRUE)
		{
			for (int i = 0; i < manager.getObj().size(); i++)
			{
				if (manager.getObj()[i]->getActive() == false)
					continue;

				if (manager.getObj()[i]->getType() == OBSTACLE)
				{
					manager.getObj()[i]->Draw(MemDC2);
					continue;
				}

				if (manager.getObj()[i]->getType() == CANNONBALL)
				{
					manager.getObj()[i]->Draw(MemDC2);
					continue;
				}

				if (manager.getObj()[i]->getType() == BLOCK)
				{
					manager.getObj()[i]->Draw(MemDC2);
					continue;
				}
			}

			manager.getCannon()->Draw(MemDC2);
		}

		// 여기까지 ~~
		BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, MemDC2, 0, 0, SRCCOPY);
		SelectObject(MemDC2, BackBit2);
		DeleteObject(BackBit1);
		DeleteDC(MemDC2);

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
		KillTimer(hWnd, timer_2);
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

VOID CALLBACK SpawnObstacle(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	manager.ObjectNew(OBSTACLE);
	SetTimer(hWnd, timer_2, spawn_interval, SpawnObstacle);
}

int CALLBACK DeadProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	wstring score = to_wstring(manager.getScore());
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hWnd, IDC_SCORE, score.c_str());
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			PostQuitMessage(WM_DESTROY);
			/*EndDialog(hWnd, LOWORD(wParam));*/
			return 1;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			RestartProgram();
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}

void RestartProgram()
{
	// 현재 실행 파일 경로 가져오기
	TCHAR szFilePath[MAX_PATH];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);

	// 새로운 프로세스 시작
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	CreateProcess(szFilePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// 핸들 해제
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// 현재 프로세스 종료
	ExitProcess(0);
}

void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT clientRect;
	GetClientRect(window, &clientRect);

	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;

	SetWindowPos(window, NULL,
		screenWidth / 2 - clientWidth / 2,
		screenHeight / 2 - clientHeight / 2,
		clientWidth, clientHeight, 0
	);
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc, TCHAR str[])
{
	Graphics graphics(hdc);

	SolidBrush brush(Color(255, 0, 0, 0));
	FontFamily fontFamily(L"궁서");
	Font font(&fontFamily, 18, FontStyleRegular, UnitPixel);
	PointF pointF(10.0f, 20.0f);
	graphics.DrawString(str, -1, &font, pointF, &brush);
}

void Gdi_End()
{
	GdiplusShutdown(g_GdiToken);
}