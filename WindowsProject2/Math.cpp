#include "Math.h"

Math::Math()
{
}

Math::~Math()
{
}

float Math::Dot(POINT p1, POINT p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

float Math::Length(POINT p)
{
	return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

float Math::Angle(POINT p1, POINT p2)
{
	return acos(Dot(p1, p2) / (Length(p1) * Length(p2))) * RAD_TO_ANGLE;
}

float Math::Distance(POINT p1, POINT p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

POINT Math::Normalize(POINT p)
{
	POINT temp;
	float temp_len = Length(p);
	temp.x = p.x / temp_len;
	temp.y = p.y / temp_len;
	return temp;
}

POINT Math::Direction(POINT p1, POINT p2)
{
	POINT temp;
	temp.x = p1.x - p2.x;
	temp.y = p1.y - p2.y;
	return Normalize(temp);
}

