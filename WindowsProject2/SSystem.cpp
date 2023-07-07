#include "SSystem.h"

SSystem::SSystem()
{
	cannon = new Cannon();
	list.clear();
	score = 0;
}

SSystem::~SSystem()
{
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
	delete cannon;
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
	}

	list.push_back(temp);
}

void SSystem::ObjectDelete(int index)
{
	list.erase(list.begin() + index);
}
