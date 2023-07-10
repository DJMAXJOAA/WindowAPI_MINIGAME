#pragma once
#include "CObject.h"

class Cannon
{
public:
	Cannon();
	~Cannon();
	void Update(POINT cur_point);
	void Draw(HDC hdc);
	bool CanItAttack();
	void setAttack();
	float getUnitVector(int XY);
	POINT getAttackPos();

private:
	POINT point;
	POINT vertex[4];
	float directionX;
	float directionY;
	float angle;
	int length;
	float attack_cycle;
	bool can_attack;
	COLORREF color;
	HBRUSH hBrush;
};
