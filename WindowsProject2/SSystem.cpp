#include "SSystem.h"

int SystemManager::getCannonballNum()
{
	return cannonball_number;
}

int SystemManager::getScore()
{
	return score;
}

int SystemManager::getLife()
{
	return life;
}

void SystemManager::reduceLife()
{
	if (life > 0)
	{
		life--;
	}
}

void SystemManager::setCannon()
{
	cannon = new Cannon();
}

void SystemManager::setCannonballNum(int x)
{
	cannonball_number += x;
}

void SystemManager::setScore(int score)
{
	this->score += score;
	printf("%d\n", this->score);
}

Cannon* SystemManager::getCannon()
{
	return cannon;
}

std::vector<CObject*> SystemManager::getObj()
{
	return list;
}

void SystemManager::ObjectNew(int type, int x, int y)
{
	CObject* temp = nullptr;

	switch (type)
	{
	case BLOCK:
		temp = new Block(x, y);
		life++;
		break;
	case CANNONBALL:
		temp = new Cannonball();
		break;
	case OBSTACLE:
		temp = new Obstacle();
		break;
	}

	if (temp != nullptr)
	{
		list.push_back(temp);
	}

	return;
}

void SystemManager::ObjectDelete()
{
	std::vector<CObject*>::iterator it;

	for (it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->getActive() == false)
		{
			list.erase(it);
			break;
		}
	}
	return;
}