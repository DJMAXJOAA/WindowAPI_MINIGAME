#include "ChildGObject.h"
#include "SSystem.h"

Block::~Block()
{
}

void Block::Update(RECT rectView)
{
}

void Block::Draw(HDC hdc)
{
}

Cannonball::Cannonball()
	: CObject(0, 0, CANNONBALL, LENGTH / 4)
{
	SystemManager& manager = SystemManager::getInstance();

	speed = 25;
	point = manager.getCannon()->getAttackPos();
	directionX = manager.getCannon()->getUnitVector(X) * -1;
	directionY = manager.getCannon()->getUnitVector(Y) * -1;
}

Cannonball::~Cannonball()
{
}

void Cannonball::Update(RECT rectView)
{
	if (this->point.x > rectView.right || this->point.x < rectView.left
		|| this->point.y > rectView.bottom || this->point.y < rectView.top)
	{
		setDeactive();
	}
	this->point.x += directionX * this->speed;
	this->point.y += directionY * this->speed;
}

void Cannonball::Draw(HDC hdc)
{
	Ellipse(hdc, point.x - length, point.y - length, point.x + length, point.y + length);
}

Obstacle::~Obstacle()
{
}

int Obstacle::RandomPt()
{
	return 0;
}

void Obstacle::Update(RECT rectView)
{
}

void Obstacle::Draw(HDC hdc)
{
}