#include "SSystem.h"

void SystemManager::setCannon()
{
	cannon = new Cannon();
}

Cannon* SystemManager::getCannon()
{
	return cannon;
}

std::vector<CObject*> SystemManager::getObj()
{
	return list;
}

void SystemManager::ObjectNew(int type)
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
	}

	list.push_back(temp);

	return;
}

void SystemManager::ObjectDelete()
{
	std::vector<CObject*> temp;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->getActive() == false)
		{
			delete list[i];
		}
		else
		{
			temp.push_back(list[i]);
		}
	}
	list = temp;
	wprintf(TEXT("cannon ball count : %d\n"), list.size());
}