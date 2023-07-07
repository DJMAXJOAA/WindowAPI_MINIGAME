#pragma once
#include "ChildGObject.h"
#include "Cannon.h"

class SSystem
{
public:
	std::vector<CObject*> list;

	SSystem();
	~SSystem();
	int ListSize();
	void ObjectNew(int type);
	void ObjectDelete(int index);

private:
	int score;
};