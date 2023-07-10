#pragma once
#include "Cannon.h"
#include "ChildGObject.h"

class SystemManager
{
private:
	SystemManager() {
		life = 0;
		cannonball_number = 0;
		list.clear();
		cannon = nullptr;
		score = 0;
	}
	SystemManager(const SystemManager& ref) {}
	SystemManager& operator=(const SystemManager& ref) {}
	~SystemManager() {}

	int life;
	int score;
	int cannonball_number;
	std::vector<CObject*> list;
	Cannon* cannon;
public:
	static SystemManager& getInstance()
	{
		static SystemManager manager;
		return manager;
	}

	std::vector<CObject*> getObj();
	Cannon* getCannon();
	int getCannonballNum();
	int getScore();
	int getLife();
	void reduceLife();
	void setCannon();
	void setCannonballNum(int x);
	void setScore(int score);
	void ObjectNew(int type, int x = 0, int y = 0);
	void ObjectDelete();
};