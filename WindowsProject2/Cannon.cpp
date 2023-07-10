#include "Cannon.h"
#include "SSystem.h"
#include "Math.h"

Cannon::Cannon()
{
	point.x = WIDTH2 / 2;
	point.y = HEIGHT2;
	length = LENGTH;
	angle = 0;

	vertex[0] = { -length * 2, -length / 4 };
	vertex[1] = { -length * 2, +length / 4 };
	vertex[2] = { 1, +length / 4 };
	vertex[3] = { 1, -length / 4 };
	directionX = 0;
	directionY = 0;

	attack_cycle = 2;
	can_attack = true;

	color = RGB(204, 204, 204);
	hBrush = CreateSolidBrush(color);
}

Cannon::~Cannon()
{
}

void Cannon::Update(POINT cur_point)
{
	Math& calculator = Math::getInstance();

	POINT temp = { 1, 0 };
	angle = calculator.Angle(temp, cur_point);
	directionX = calculator.Normalize(calculator.ChangeVector(cur_point), X);
	directionY = calculator.Normalize(calculator.ChangeVector(cur_point), Y);
}

void Cannon::Draw(HDC hdc)
{
	HBRUSH oldBrush;

	oldBrush = (HBRUSH)SelectObject(hdc, this->hBrush);

	float angle2 = angle * ANGLE_TO_RAD;
	POINT temp[4];
	for (int i = 0; i < 4; i++)
	{
		temp[i].x = point.x + (vertex[i].x * cosf(angle2) - vertex[i].y * sinf(angle2));
		temp[i].y = point.y + (vertex[i].x * sinf(angle2) + vertex[i].y * cosf(angle2));
	}
	Polygon(hdc, temp, 4);

	oldBrush = (HBRUSH)SelectObject(hdc, this->hBrush);
	Ellipse(hdc, point.x - length, point.y - length, point.x + length, point.y + length);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);
}

bool Cannon::CanItAttack()
{
	SystemManager& manager = SystemManager::getInstance();

	if (manager.getCannonballNum() >= 3)
		return false;
	return true;
}

void Cannon::setAttack()
{
}

float Cannon::getUnitVector(int XY)
{
	if (XY == X)
	{
		return directionX;
	}
	if (XY == Y)
	{
		return directionY;
	}
}

POINT Cannon::getAttackPos()
{
	float angle2 = angle * ANGLE_TO_RAD;
	POINT temp;

	temp.x = point.x + (vertex[0].x * cosf(angle2) - 1 * sinf(angle2));
	temp.y = point.y + (vertex[0].x * sinf(angle2) + 1 * cosf(angle2));

	return temp;
}