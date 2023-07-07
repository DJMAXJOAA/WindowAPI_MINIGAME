#include "Cannon.h"
#include "Math.h"

Math cal_a;

Cannon::Cannon()
{
	point.x = WIDTH2 / 2;
	point.y = HEIGHT2;
	length = LENGTH;
	angle = 0;  

	vertex[0] = { - length * 2, - length / 4 };
	vertex[1] = { - length * 2, + length / 4 };
	vertex[2] = { 1, + length / 4 };
	vertex[3] = { 1, - length / 4 };
	directionX = 0;
	directionY = 0;

	attack_cycle = 2;
	can_attack = true;
}

Cannon::~Cannon()
{
}

void Cannon::Update(POINT cur_point)
{
	POINT temp = { 1, 0 };
	angle = cal_a.Angle(temp, cur_point);
	directionX = cal_a.Normalize(cal_a.ChangeVector(cur_point), X);
	directionY = cal_a.Normalize(cal_a.ChangeVector(cur_point), Y);
}

void Cannon::Draw(HDC hdc)
{
	float angle2 = angle * ANGLE_TO_RAD;
	POINT temp[4];
	for (int i = 0; i < 4; i++)
	{
		temp[i].x = point.x + (vertex[i].x * cosf(angle2) - vertex[i].y * sinf(angle2));
		temp[i].y = point.y + (vertex[i].x * sinf(angle2) + vertex[i].y * cosf(angle2));
	}
	wprintf(TEXT("%f, %f, %f\n"), angle, directionX, directionY);
	Polygon(hdc, temp, 4);
	Ellipse(hdc, point.x - length, point.y - length, point.x + length, point.y + length);
}

bool Cannon::CanItAttack()
{
	return false;
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

	temp.x = point.x + (1 * cosf(angle2) - 1 * sinf(angle2));
	temp.y = point.y + (1 * sinf(angle2) + 1 * cosf(angle2));
	
	return temp;
}
