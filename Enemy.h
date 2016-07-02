#pragma once

#include <vector>

#include "Abstract.h"
#include "Vector2.h"
#include "Collision.h"

class HueKeeper{
public:
	enum mode{
		constant,
		rainbow,
	};
	mode mode_;
	double hue;
	double dHue;
	double rainbowDif;
	HueKeeper();
	double getHue(int num, int allnum);
	void rotHue();
};

class IMover{
public:
	IMover(Vector2 &pos);
	Vector2 firstPos;
	lint eFrame;
	void update(Vector2 &pos);
	virtual void move(Vector2 &pos) = 0;
};

class MoverToPlayer : public IMover{
public:
	MoverToPlayer(Vector2 &pos);
	double speed;
	Vector2 vel;
	virtual void move(Vector2 &pos);
};

class MoverToCenter : public IMover{
public:
	MoverToCenter(Vector2 &pos);
	double speed;
	Vector2 vel;
	virtual void move(Vector2 &pos);
};


class Mover3Pos : public IMover{
public:
	Mover3Pos(Vector2 &pos);
	double moveRatePal;
	Vector2 targetPos;
	int moveCount;
	int moveCountMax;
	virtual void move(Vector2 &pos);
};

class Mover1Pos : public IMover{
public:
	Mover1Pos(Vector2 &pos);
	double moveRatePal;
	Vector2 targetPos;
	virtual void move(Vector2 &pos);
};

class IWeapon{
public:
	lint eFrame;
	HueKeeper hueKeeper;
	IWeapon();
	void update(Vector2 &pos);
	virtual void shot(Vector2 &pos) = 0;
};

class WeaponToPlayer : public IWeapon{
public:
	WeaponToPlayer(Vector2 &pos);
	double speed;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponToPlayerSomeNum : public IWeapon{
public:
	WeaponToPlayerSomeNum(Vector2 &pos);
	double speed;
	int num;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};


class WeaponToPlayerParallel : public IWeapon{
public:
	WeaponToPlayerParallel(Vector2 &pos);
	double speed;
	double distOnBullet;
	int num;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponToPlayerNWay : public IWeapon{
public:
	WeaponToPlayerNWay(Vector2 &pos);
	double speed;
	double angleDif;
	int num;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponSpreadSinAngle : public IWeapon{
public:
	WeaponSpreadSinAngle(Vector2 &pos);
	double speed;
	double firstAngle;
	double angleDif;
	double shotAngle;
	double shotAnglePlus;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};


class WeaponAround : public IWeapon{
public:
	WeaponAround(Vector2 &pos);
	double speed;
	int num;
	double baseAngle;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponAroundSomeNum : public WeaponAround{
public:
	WeaponAroundSomeNum(Vector2 &pos);
	int numOnLine;
	double dAngle;
	virtual void shot(Vector2 &pos);
};

class WeaponAroundToPlayer : public IWeapon{
public:
	WeaponAroundToPlayer(Vector2 &pos);
	double speed;
	int num;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponAroundSinAngle : public IWeapon{
public:
	WeaponAroundSinAngle(Vector2 &pos);
	double firstAngle;
	double angleDif;
	double shotAngle;
	double shotAnglePlus;
	double speed;
	int num;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};

class WeaponAnglePlus : public IWeapon{
public:
	WeaponAnglePlus(Vector2 &pos);
	double speed;
	double nowAngle;
	double dAngle;
	int cool;
	int rate;
	virtual void shot(Vector2 &pos);
};


class IGraphic{
public:
	IGraphic();
	lint eFrame;
	HueKeeper hueKeeper;
	double alpha;
	virtual void update();
	virtual void draw(Vector2 &pos) = 0;
	virtual double getRadius() = 0;
};

class GraphicCore : public IGraphic{
public:
	std::string gHandleName;
	double rotAngle;
	double coreHue;
	GraphicCore();
	void draw(Vector2 &pos);
	double getRadius();
};

class GraphicRing : public IGraphic{
public:
	std::string gHandleName;
	double exRate;
	double hue;
	GraphicRing();
	void draw(Vector2 &pos);
	double getRadius();
};

class GraphicOnCircle : public IGraphic{
public:
	int objNum;
	double firstAngle;
	double radius;
	Vector2 exRate;
	double angleEFrameRate;
	double rotAngle;
	std::string gHandleName;

	GraphicOnCircle();
	void draw(Vector2 &pos);
	double getRadius();
};

class GraphicOnCircleRect : public IGraphic{
public:
	int objNum;
	double firstAngle;
	double radius;
	Vector2 exRate;
	double angleEFrameRate;
	double rotAngle;
	std::string gHandleName;

	GraphicOnCircleRect();
	void draw(Vector2 &pos);
	double getRadius();
};

class GraphicOnCircleRTri : public IGraphic{
public:
	int objNum;
	double firstAngle;
	double radius;
	Vector2 exRate;
	double angleEFrameRate;
	double rotAngle;
	std::string gHandleName;

	GraphicOnCircleRTri();
	void draw(Vector2 &pos);
	double getRadius();
};

class GraphicOnCircleNoRotate : public IGraphic{
public:
	int objNum;
	double firstAngle;
	double radius;
	Vector2 exRate;
	double angleEFrameRate;
	double rotAngle;
	std::string gHandleName;

	GraphicOnCircleNoRotate();
	void draw(Vector2 &pos);
	double getRadius();
};


class IEnemy : public IObject{
public:
	IEnemy(Vector2 pos_);

	std::shared_ptr<ICollision> col;
	Vector2 pos;
	double canShotPosY;
	double hp;
	std::shared_ptr<IMover> mover;
	std::vector<std::shared_ptr<IWeapon>> weapon;
	std::vector<std::shared_ptr<IGraphic>> graphic;

	void isScreenOut();
	void checkHp();
	virtual void update() = 0;
	virtual void draw() = 0;
};

class Enemy_ : public IEnemy{
public:
	Enemy_(Vector2 pos_);
	void update();
	void draw();
};

class ResultEnemyEffect : public IEnemy{
public:
	ResultEnemyEffect(Vector2 pos_);
	Vector2 vel;
	void update();
	void draw();
};