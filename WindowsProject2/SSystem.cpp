#include "SSystem.h"

SSystem::SSystem()
{
	list.clear();
	score = 0;
}

SSystem::~SSystem()
{
	
}

void SSystem::ObjectNew(int type, SSystem &manager)
{
	CObject* temp;

	switch (type)
	{
	case BLOCK:
		temp = new Block();
		break;
	case CANNONBALL:
		temp = new Cannonball(manager);
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
