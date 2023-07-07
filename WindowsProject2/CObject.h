#pragma once
#include "framework.h"

enum Type
{
	BLOCK, CANNONBALL, OBSTACLE, CANNON
};

enum POINTXY
{
	X, Y
};

class CObject
{
public:
	CObject(int x, int y, int type, int length);
	~CObject();

	int getXY(int XY);
	POINT getPoint();
	bool isitCollide(CObject &x);
	void setCollide(bool TF);
	virtual void Update(HDC hdc) = 0;

protected:
	POINT point;
	int type;
	bool collide;
	int length;
};