#pragma once

#include "resource.h"
#include "SSystem.h"
#include "Cannon.h"
#include "ChildGObject.h"
#include "CObject.h"
#include "Math.h"

VOID CALLBACK SpawnObstacle(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
int CALLBACK DeadProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RestartProgram();
void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle);

void Gdi_Init(); // winmain의 기본 메세지 루프 사이에 들어가야함
void Gdi_Draw(HDC hdc, TCHAR str[]);
void Gdi_End(); // winmain의 맨마지막 부분에 들어가야함