#pragma once
#include "Cannon.h"
#include "ChildGObject.h"

class SSystem
{
public:
	std::vector<CObject*> list;
	Cannon* cannon;

	SSystem();
	~SSystem();
	void ObjectNew(int type, SSystem &manager);
	void ObjectDelete(int index);

private:
	int score;
};