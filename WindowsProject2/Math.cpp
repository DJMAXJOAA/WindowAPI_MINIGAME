#include "Math.h"

Math::Math()
{
}

Math::~Math()
{
}

POINT Math::ChangeVector(POINT p)
{
	POINT temp;
	temp.x = WIDTH2 / 2 - p.x;
	temp.y = HEIGHT2 - p.y;
	return temp;
}

float Math::Random(float min, float max)
{
	std::random_device rand;
	std::mt19937_64 random(rand());
	std::uniform_real_distribution<float> dist1(min, max);

	float temp = 0;
	while (!temp)
	{
		temp = dist1(random);
	}

	return temp;
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
	POINT temp = ChangeVector(p2);
	return acos(Dot(p1, temp) / (Length(p1) * Length(temp))) * RAD_TO_ANGLE;
}

float Math::Distance(POINT p1, POINT p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float Math::Normalize(POINT p, int XY)
{
	POINT temp;
	float temp_len = Length(p);
	if (XY == X)
	{
		return p.x / temp_len;
	}
	if (XY == Y)
	{
		return p.y / temp_len;
	}
}