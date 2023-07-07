#include "ChildGObject.h"

Block::~Block()
{
}

void Block::Update()
{
}

void Block::Draw(HDC hdc)
{
}

Cannonball::Cannonball(SSystem manager)
	: CObject(0, 0, CANNONBALL, LENGTH/2)
{
	speed = 10;
	point = manager.cannon->getAttackPos();
	directionX = manager.cannon->getUnitVector(X);
	directionY = manager.cannon->getUnitVector(Y);
}

Cannonball::~Cannonball()
{
}

void Cannonball::Update(RECT rectView, SSystem manager)
{
    if (this->point.x > rectView.right)
    {
        manager.ObjectDelete(index);
    }
    else if (this->point.x < rectView.left)
    {
        this->direction.x *= -1.0;
        this->point.x += 20;
    }
    else if (this->point.y > rectView.bottom)
    {
        this->direction.y *= -1.0;
        this->point.y -= 20;
    }
    else if (this->point.y < rectView.top)
    {
        this->direction.y *= -1.0;
        this->point.y += 20;
    }
    this->point.x += this->direction.x * this->speed;
    this->point.y += this->direction.y * this->speed;
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

void Obstacle::Update()
{
}

void Obstacle::Draw(HDC hdc)
{
}
