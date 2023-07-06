#pragma once
#include "framework.h"

enum Type
{
	CANNONBALL, OBSTACLE, BLOCK
};

class GObject
{
private:
	POINT point;
	int type;
	bool collide;

	
public:
	GObject();
	~GObject();
	bool isitCollide();
	virtual void Update() = 0;

};

GObject::GObject()
{
}

GObject::~GObject()
{
}
