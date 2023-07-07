#pragma once
#include "framework.h"

class Math
{
public:
	Math();
	~Math();

	float Dot(POINT p1, POINT p2);
	float Length(POINT p);
	float Angle(POINT p1, POINT p2);
	float Distance(POINT p1, POINT p2);
	POINT Normalize(POINT p);
	POINT Direction(POINT p1, POINT p2);
};