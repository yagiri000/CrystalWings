#pragma once

#include <memory>
#include "Vector2.h"
#include "Abstract.h"
#include "Collision.h"


class IPlayerBullet : public IObject{
public:
	std::string gHandleName;
	int eFrame;
	double alpha;
	double damage;
	Vector2 pos;
	IPlayerBullet(Vector2 pos_, const std::string& gHName, double damage_);
	std::shared_ptr<ICollision> col;
	virtual void update();
	virtual void isCrash() = 0;
	virtual void isScreenOut() = 0;
	virtual void move() = 0;
	virtual void draw() = 0;
};


class PlayerBulletNormal : public IPlayerBullet
{
public:
	//double hue;
	PlayerBulletNormal(Vector2& pos_, Vector2& vel_, double length_);

	Vector2 vel;
	double length;
	Vector2 graphicSize;

	virtual void isCrash();
	virtual void isScreenOut();
	virtual void move();
	virtual void draw();
};


class PlayerBulletBomb : public IPlayerBullet
{
public:
	PlayerBulletBomb(Vector2& pos_);

	const double radius;
	Vector2 vel;

	virtual void isCrash();
	virtual void isScreenOut();
	virtual void move();
	virtual void draw();
};