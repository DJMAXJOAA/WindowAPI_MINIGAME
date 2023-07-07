#include "Cannon.h"

Cannon::~Cannon()
{
}

void Cannon::Update(HDC hdc)
{
	Ellipse(hdc, 0, 0, 40, 40);
}

bool Cannon::CanItAttack()
{
	return false;
}

void Cannon::setAttack()
{
}
