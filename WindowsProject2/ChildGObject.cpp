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

Cannonball::Cannonball(SSystem manager)
	: CObject(0, 0, CANNONBALL, LENGTH/4)
{
	speed = 25;
	point = manager.cannon->getAttackPos();
	directionX = manager.cannon->getUnitVector(X) * -1;
	directionY = manager.cannon->getUnitVector(Y) * -1;
}

Cannonball::~Cannonball()
{
}

void Cannonball::Update(RECT rectView)
{
    //if (this->point.x > rectView.right || this->point.x < rectView.left
    //    || this->point.y > rectView.bottom || this->point.y < rectView.top)
    //{
    //    
    //}
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
