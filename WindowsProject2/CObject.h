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
	bool getCollide(CObject& x);
	bool getActive();
	int getType();
	int getLength();
	void setCollide(bool TF);
	void setDeactive();
	void setColor(int R, int G, int B);
	virtual void Update(RECT rectView) = 0;
	virtual void Draw(HDC hdc) = 0;

protected:
	POINT point;
	int type;
	bool collide;
	int length;
	int index;
	bool active;
	COLORREF color;
	HBRUSH hBrush;
};
