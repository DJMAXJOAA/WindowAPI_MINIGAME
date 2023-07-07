#include "CObject.h"
#include "Math.h"
#include "SSystem.h"

Math cal_b;

CObject::CObject(int x, int y, int type, int length)
{
	point.x = x;
	point.y = y;
	this->length = length;
	this->type = type;
	index = 0;
	collide = false;
}

CObject::~CObject()
{
}

int CObject::getXY(int XY)
{
	if (XY == X)
		return point.x;
	if (XY == Y)
		return point.y;
}

POINT CObject::getPoint()
{
	return point;
}

bool CObject::isitCollide(CObject &x)
{
	return false;
}

void CObject::setCollide(bool TF)
{
	if (TF == TRUE)
		collide = true;
	if (TF == FALSE)
		collide = false;
}

