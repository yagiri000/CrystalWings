//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------

//-------------------------------------------
//
//                n. i. a.
//
//                         Effect Draw System
//-------------------------------------------

#pragma once

#include <vector>
#include <functional>

#include "Abstract.h"
#include "Vector2.h"


//Effectsの個々のエフェクトの基底クラス

class IEffect : public IObject{
public:
	Vector2 pos;
	Vector2 center;
	Vector2 exRate;
	double angle;

	double alpha;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 exRatePlus;
	double sppedrate;

	double angleplus;
	double alphaplus;
	int turnflag;
	int blendmode;

	int ghandle;

	int elapsedtime;
	int deleteframe;

	double PI;

	IEffect();


	virtual void set(
		const Vector2 &pos,
		const Vector2 &center,
		const Vector2 &exRate,
		double angle,

		double alpha,
		const Vector2 &velocity,
		const Vector2 &acceleration,
		const Vector2 &exRatePlus,
		double sppedrate,

		double angleplus,
		double alphaplus,
		int turnflag,
		int blendmode,

		int ghandle,

		int deleteframe
		);

	virtual void move();
	virtual void update();
	virtual void draw();
	void wait(int f);
};


//エフェクトを生成するクラスの基底クラス
class ISet : public IEffect{
public:
	ISet();

	virtual void move();
	virtual void update();
	virtual void draw();
};




//エフェクトを生成するクラスの基底クラス
class PlayerDeadBomb : public ISet{
public:
	PlayerDeadBomb(const Vector2 &pos);
	virtual void move();
};

//エフェクトを生成するクラスの基底クラス
class EnemyDeadBomb : public ISet{
public:
	EnemyDeadBomb(const Vector2 &pos);
	virtual void move();
};





//個々のエフェクトの設定ファイル


class PlayerTrail : public IEffect{
public:
	PlayerTrail(const Vector2 &pos);
};

class Trail : public IEffect{
public:
	Trail(const Vector2 &pos);
};

class Debri : public IEffect{
public:
	Debri(const Vector2 &pos);
};

class TitleEf : public IEffect{
public:
	TitleEf(const Vector2 &pos);
	virtual void update();
};

class StrEf : public IEffect{
public:
	std::string str;
	StrEf(const Vector2 &pos, const std::string &str_);
	virtual void draw();
};

class fire : public IEffect{
public:
	fire(const Vector2 &pos);
};


class slash : public IEffect{
public:
	slash(const Vector2 &pos);
};


class bomb : public IEffect{
public:
	bomb(const Vector2 &pos);
};


class CirBlank : public IEffect{
public:
	int col;
	CirBlank(const Vector2 &pos);
	virtual void draw();
};


class BoxBlank : public IEffect{
public:
	int col;
	BoxBlank(const Vector2 &pos);
	virtual void draw();
};


class BombSplash : public IEffect{
public:
	int col;
	BombSplash(const Vector2 &pos);
	virtual void draw();
};


class BombRetro : public IEffect{
public:
	BombRetro(const Vector2 &pos);
	virtual void move();
};
