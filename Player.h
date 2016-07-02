#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Vector2.h"
#include "Collision.h"




class IPlayerState{
public:
	IPlayerState();
	virtual int getBombNum() = 0;
	virtual Vector2 getPos() = 0;
	virtual std::string getStateString() = 0;
	virtual std::unique_ptr<IPlayerState> update() = 0;
	virtual void draw() = 0;
};

class PlayerWing : public IObject{
public:
	PlayerWing();
	int eFrame;
	double radius;
	double targetRadius;
	double moveRateVal;
	int wingNum;
	Vector2 gCenter;
	Vector2 gExRate;
	std::string gName;
	void update();
	void draw();
};



class PlayerBomb{
public:
	PlayerBomb();
	int eFrame;
	int rate;
	int cool;
	int remainingBomb;
	bool update(Vector2 &pos);
	void draw();
};


class PlayerWeapon{
public:
	PlayerWeapon();
	int eFrame;
	int shotCool;
	int shotRate;
	Vector2 shotVel;
	void update(Vector2 &pos);
	void draw();
};

class PSAlive : public IPlayerState{
public:
	PSAlive();

	PlayerWing playerWing;
	PlayerWeapon pWeapon;
	PlayerBomb pBomb;
	Vector2 pos;
	double speed;
	double radius;
	Vector2 exRate;
	double tiltAngle;
	int invincibleFrameMax;//>0‚Å–³“G
	int invincibleFrame;
	lint eFrame;
	std::shared_ptr<ICollision> col;
	

	void keyMove();
	void tiltUpdate();
	void shot();
	bool isCrash();
	virtual int getBombNum();
	virtual Vector2 getPos();
	virtual std::string getStateString();
	virtual std::unique_ptr<IPlayerState> update();
	virtual void draw();
};


class PSDead : public IPlayerState{
public:
	PSDead();
	Vector2 pos;
	int countFrame;
	int rebirthFrame;
	virtual int getBombNum();
	virtual Vector2 getPos();
	virtual std::string getStateString();
	virtual std::unique_ptr<IPlayerState> update();
	virtual void draw();
};




class Player : public IObject
{
public:
	int remainingLives;
	int eFrame;
	Vector2 pos;
	std::unique_ptr<IPlayerState> state;
	static Vector2 getFirstPos();
	Player();
	std::string getStateString();
	int getBombNum();
	void deadRemainMinus();
	void update();
	void draw();
};