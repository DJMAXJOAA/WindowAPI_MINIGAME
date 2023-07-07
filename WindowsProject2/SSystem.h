#pragma once
#include "ChildGObject.h"
#include "Cannon.h"

class SSystem
{
public:
	std::vector<CObject*> list;
	Cannon* cannon;

	SSystem();
	~SSystem();
	void ObjectNew(int type);
	void ObjectDelete(int index);

private:
	int score;
};