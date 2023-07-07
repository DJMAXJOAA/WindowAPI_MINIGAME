#pragma once
#include "CObject.h"

/* 블럭 */
/* 블럭 */
class Block : public CObject
{
public:
	Block() : CObject(0, 0, BLOCK, LENGTH) {
		health = 3;
		dead = false;
	};
	~Block();
	void Update(HDC hdc) override;

private:
	int health;
	bool dead;
};


/* 포탄 */
/* 포탄 */
class Cannonball : public CObject
{
public:
	Cannonball() : CObject(0, 0, CANNONBALL, LENGTH) {
		speed = 10;
	};
	~Cannonball();
	void Update(HDC hdc) override;

private:
	float speed;
};


/* 장애물 */
/* 장애물 */
class Obstacle : public CObject
{
public:
	Obstacle() : CObject(RandomPt(), 0, OBSTACLE, LENGTH) {
		speed = 10;
		angle = 1;
	};
	~Obstacle();
	int RandomPt();
	void Update(HDC hdc) override;

private:
	float speed;
	float angle;
};

