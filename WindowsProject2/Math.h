#pragma once
#include "framework.h"

class Math
{
private:
	Math();
	~Math();
public:
	static Math& getInstance()
	{
		static Math* instance = new Math();
		return *instance;
	}

	POINT ChangeVector(POINT p);
	float Dot(POINT p1, POINT p2);
	float Length(POINT p);
	float Angle(POINT p1, POINT p2);
	float Distance(POINT p1, POINT p2);
	float Normalize(POINT p, int XY);
};