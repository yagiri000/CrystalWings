#pragma once

#include <vector>
#include <memory>
#include "Vector2.h"
#include "Abstract.h"
#include "Collision.h"


class IEnemyBullet : public IObject
{
public:
	std::shared_ptr<ICollision> col;

	double hue;
	std::string gHandleName;
	int eFrame;
	IEnemyBullet(std::shared_ptr<ICollision> col_, double hue_, const std::string& gHName);
	virtual void update();
	virtual void isScreenOut() = 0;
	virtual void kill() = 0;//É{ÉÄÇ»Ç«Ç≈è¡Ç≥ÇÍÇΩéûóp
	virtual void move() = 0;
	virtual void draw() = 0;
};

class EBStraightLine : public IEnemyBullet
{
public:
	EBStraightLine(Vector2& pos_, Vector2& vel_, double length_, double hue_);

	Vector2 pos;
	Vector2 vel;
	double length;
	Vector2 graphicSize;

	virtual void isScreenOut();
	virtual void kill();
	virtual void move();
	virtual void draw();
};

class EBStraightLineSpeedEaseCos : public EBStraightLine
{
public:
	EBStraightLineSpeedEaseCos(Vector2& pos_, Vector2& vel_, double length_, double hue_);
	int easeAllFrame;
	double easeCos(int frame, int allFrame);
	virtual void move();
};

