#include "Cannon.h"

Cannon::~Cannon()
{
}

void Cannon::Update(HDC hdc)
{
	Rectangle(hdc, point.x - length, point.y - length, point.x+length, point.y+length);
}

bool Cannon::CanItAttack()
{
	return false;
}

void Cannon::setAttack()
{
}
