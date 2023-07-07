#pragma once
#include "framework.h"

enum Type
{
	BLOCK, CANNONBALL, OBSTACLE
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
	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;

protected:
	POINT point;
	int type;
	bool collide;
	int length;
	int index;
};