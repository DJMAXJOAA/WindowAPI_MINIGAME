#pragma once
#include "framework.h"

class Math
{
public:
	Math();
	~Math();

	POINT ChangeVector(POINT p);
	float Dot(POINT p1, POINT p2);
	float Length(POINT p);
	float Angle(POINT p1, POINT p2);
	float Distance(POINT p1, POINT p2);
	float Normalize(POINT p, int XY);
};