#include "SSystem.h"

SSystem::SSystem()
{
	list.clear();
	score = 0;
}

SSystem::~SSystem()
{
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
}

int SSystem::ListSize()
{
	return list.size();
}

void SSystem::DoubleBuffering(HWND hWnd, HDC hdc, RECT rect)
{
	GetClientRect(hWnd, &rect);
	hMemDC1 = CreateCompatibleDC(hdc);
	BackBit1 = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	BackBit2 = (HBITMAP)SelectObject(hMemDC1, BackBit1);
	PatBlt(hMemDC1, 0, 0, rect.right, rect.bottom, WHITENESS);
	
	hMemDC2 = hdc;
	hdc = hMemDC1;
	hMemDC1 = hMemDC2;
}

void SSystem::ScreenEnd(HWND hWnd, HDC hdc, RECT rect)
{
	hMemDC2 = hdc;
	hdc = hMemDC1;
	hMemDC1 = hMemDC2;

	GetClientRect(hWnd, &rect);
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC1, 0, 0, SRCCOPY);
	SelectObject(hMemDC1, BackBit2);
	DeleteObject(BackBit1);
	DeleteDC(hMemDC1);
}

void SSystem::PaintScreen(HWND hWnd, HDC hdc, RECT rect)
{
}

void SSystem::ObjectNew(int type)
{
	CObject* temp;

	switch (type)
	{
	case BLOCK:
		temp = new Block();
		break;
	case CANNONBALL:
		temp = new Cannonball();
		break;
	case OBSTACLE:
		temp = new Obstacle();
		break;
	case CANNON:
		temp = new Cannon();
	}

	list.push_back(temp);
}

void SSystem::ObjectDelete(int index)
{
	list.erase(list.begin() + index);
}
