#pragma once
#include "CObject.h"

class Cannon : public CObject
{
public:
	Cannon() : CObject(400, 0, CANNON, LENGTH)
	{
		angle = 0;
		attack_cycle = 2;
		can_attack = true;
	}
	~Cannon();
	void Update(HDC hdc) override;
	bool CanItAttack();
	void setAttack();

private:
	float angle;
	float attack_cycle;
	bool can_attack;
};

