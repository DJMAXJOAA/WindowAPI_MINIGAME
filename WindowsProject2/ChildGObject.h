#pragma once
#include "CObject.h"

/* 블럭 */
/* 블럭 */
class Block : public CObject
{
public:
	Block(int x, int y) : CObject(0, 0, BLOCK, LENGTH) {
		point.x = x;
		point.y = y;
		health = 3;
		color = RGB(153, 153, 0);
		hBrush = CreateSolidBrush(color);
	};
	~Block();
	void Update(RECT rectView) override;
	void Draw(HDC hdc) override;
	void getDamaged(int damage);
	int getHealth();

private:
	int health;
};

/* 포탄 */
/* 포탄 */
class Cannonball : public CObject
{
public:
	Cannonball();
	~Cannonball();
	void Update(RECT rectView) override;
	void Draw(HDC hdc) override;

private:
	float speed;
	float directionX;
	float directionY;
};

/* 장애물 */
/* 장애물 */
class Obstacle : public CObject
{
public:
	Obstacle();
	~Obstacle();
	void Update(RECT rectView) override;
	void Draw(HDC hdc) override;

private:
	float directionX;
	float directionY;
	float speed;
};
