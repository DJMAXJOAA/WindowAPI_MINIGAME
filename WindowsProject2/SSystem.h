#pragma once
#include "ChildGObject.h"
#include "Cannon.h"

class SSystem
{
public:
	std::vector<CObject*> list;

	SSystem();
	~SSystem();
	void ScreenInit(HWND hWnd, HDC hdc, RECT rect, HDC MemDC);
	void ScreenPaint(HWND hWnd, HDC hdc, RECT rect, HDC MemDC);
	void ScreenRelease(HWND hWnd, HDC hdc, RECT rect, HDC MemDC);
	void ObjectNew(int type);
	void ObjectDelete(int index);

private:
	int score;
	RECT rect;
};