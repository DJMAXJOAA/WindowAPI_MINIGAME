#include "ChildGObject.h"
#include "SSystem.h"
#include "Math.h"

Block::~Block()
{
}

void Block::Update(RECT rectView)
{
	SystemManager& manager = SystemManager::getInstance();
	Math& calculator = Math::getInstance();

	for (int i = 0; i < manager.getObj().size(); i++)
	{
		if (manager.getObj()[i]->getType() == OBSTACLE)
		{
			if (manager.getObj()[i]->getXY(Y) >= point.y - length / 2 &&
				manager.getObj()[i]->getXY(X) <= point.x + length && manager.getObj()[i]->getXY(X) >= point.x - length)
			{
				if (getHealth() > 1)
				{
					getDamaged(1);
					setColor(getHealth() * 51, getHealth() * 51, 0);
				}
				else
				{
					manager.reduceLife();
					setDeactive();
				}
				manager.getObj()[i]->setDeactive();

				break;
			}
		}
	}
}

void Block::Draw(HDC hdc)
{
	HBRUSH oldBrush;

	oldBrush = (HBRUSH)SelectObject(hdc, this->hBrush);

	Rectangle(hdc, point.x - length, point.y - length / 2, point.x + length, point.y + length / 2);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);
}

void Block::getDamaged(int damage)
{
	health -= damage;
}

int Block::getHealth()
{
	return health;
}

Cannonball::Cannonball()
	: CObject(0, 0, CANNONBALL, LENGTH / 4)
{
	SystemManager& manager = SystemManager::getInstance();
	manager.setCannonballNum(1);

	speed = 30;
	point = manager.getCannon()->getAttackPos();
	directionX = manager.getCannon()->getUnitVector(X) * -1;
	directionY = manager.getCannon()->getUnitVector(Y) * -1;
	color = RGB(255, 255, 255);
	hBrush = CreateSolidBrush(color);
}

Cannonball::~Cannonball()
{
}

void Cannonball::Update(RECT rectView)
{
	SystemManager& manager = SystemManager::getInstance();
	Math& calculator = Math::getInstance();

	// 벽과 충돌
	if (this->point.x > rectView.right || this->point.x < rectView.left
		|| this->point.y > rectView.bottom || this->point.y < rectView.top)
	{
		setDeactive();
		if (manager.getCannonballNum() > 0)
		{
			manager.setCannonballNum(-1);
		}
		return;
	}

	// 장애물과 충돌
	for (int i = 0; i < manager.getObj().size(); i++)
	{
		if (manager.getObj()[i]->getType() == OBSTACLE)
		{
			if (calculator.Distance(point, manager.getObj()[i]->getPoint()) < length + manager.getObj()[i]->getLength())
			{
				manager.setScore(SCORE);
				setDeactive();
				manager.getObj()[i]->setDeactive();
				if (manager.getCannonballNum() > 0)
				{
					manager.setCannonballNum(-1);
				}
				return;
			}
		}
	}
	this->point.x += directionX * this->speed;
	this->point.y += directionY * this->speed;
}

void Cannonball::Draw(HDC hdc)
{
	HBRUSH oldBrush;

	oldBrush = (HBRUSH)SelectObject(hdc, this->hBrush);

	Ellipse(hdc, point.x - length, point.y - length, point.x + length, point.y + length);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);
}

Obstacle::Obstacle()
	: CObject(0, 0, OBSTACLE, LENGTH / 5)
{
	Math& calculator = Math::getInstance();

	point.x = calculator.Random(0.01, WIDTH2);
	POINT arrival = { calculator.Random(0, WIDTH2) - point.x, HEIGHT2 };

	directionX = calculator.Normalize(arrival, X);
	directionY = 1.0;
	speed = 15;
	color = RGB(0, 0, 0);
	hBrush = CreateSolidBrush(color);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(RECT rectView)
{
	Math& calculator = Math::getInstance();

	// 벽과 충돌
	if (this->point.x > rectView.right || this->point.x < rectView.left
		|| this->point.y > rectView.bottom || this->point.y < rectView.top)
	{
		setDeactive();
	}
	this->point.x += directionX * this->speed;
	this->point.y += directionY * this->speed;
}

void Obstacle::Draw(HDC hdc)
{
	HBRUSH oldBrush;

	oldBrush = (HBRUSH)SelectObject(hdc, this->hBrush);

	Ellipse(hdc, point.x - length, point.y - length, point.x + length, point.y + length);

	SelectObject(hdc, oldBrush);
	DeleteObject(oldBrush);
}