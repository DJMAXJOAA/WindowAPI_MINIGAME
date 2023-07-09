#include "CObject.h"
#include "Math.h"
#include "SSystem.h"

CObject::CObject(int x, int y, int type, int length)
{
	point.x = x;
	point.y = y;
	this->length = length;
	this->type = type;
	index = 0;
	collide = false;
	active = true;
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

bool CObject::getCollide(CObject& x)
{
	return false;
}

bool CObject::getActive()
{
	return active;
}

void CObject::setCollide(bool TF)
{
	if (TF == TRUE)
		collide = true;
	if (TF == FALSE)
		collide = false;
}

void CObject::setDeactive()
{
	active = false;
}