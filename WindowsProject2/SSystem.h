#pragma once
#include "Cannon.h"
#include "ChildGObject.h"

class SystemManager
{
private:
	SystemManager() {
		list.clear();
		cannon = nullptr;
		score = 0;
	}
	SystemManager(const SystemManager& ref) {}
	SystemManager& operator=(const SystemManager& ref) {}
	~SystemManager() {}

	int score;
	std::vector<CObject*> list;
	Cannon* cannon;
public:
	static SystemManager& getInstance()
	{
		static SystemManager manager;
		return manager;
	}

	void setCannon();
	Cannon* getCannon();
	std::vector<CObject*> getObj();
	void ObjectNew(int type);
	void ObjectDelete();
};