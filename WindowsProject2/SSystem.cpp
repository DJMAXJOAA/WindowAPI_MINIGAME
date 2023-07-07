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

void SSystem::ScreenInit(HWND hWnd, HDC hdc, RECT rect, HDC MemDC)
{
	
}

void SSystem::ScreenRelease(HWND hWnd, HDC hdc, RECT rect, HDC MemDC)
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
