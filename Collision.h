//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------

#pragma once

#include <memory>
#include "Func.h"
#include "Vector2.h"


class ICollision
{
public:
	enum col_kind
	{
		point,
		line,
		circle,
		box,
	};
	ICollision(col_kind i_kind);
	virtual Vector2 getPos() = 0;
	col_kind kind;
};


class ColPoint : public ICollision
{
public:
	ColPoint();
	ColPoint(Vector2 pos_);
	virtual Vector2 getPos();
	Vector2 pos;
};


class ColLine : public ICollision
{
public:
	ColLine();
	ColLine(Vector2 start_, Vector2 end_);
	virtual Vector2 getPos();
	Vector2 start;
	Vector2 end;
};


class ColCircle : public ICollision
{
public:
	ColCircle();
	ColCircle(Vector2 pos_, double radius_);
	virtual Vector2 getPos();
	Vector2 pos;
	double radius;
};


class ColBox : public ICollision
{
public:
	ColBox();
	ColBox(Vector2 pos_, Vector2 size_);
	virtual Vector2 getPos();
	Vector2 pos;
	Vector2 size;
};


class Collsion
{
public:
	static bool IsCrash(std::shared_ptr<ICollision> col1, std::shared_ptr<ICollision> col2);
	static void draw(std::shared_ptr<ICollision> ptr, int color);
	static std::shared_ptr<ICollision> testCol();
	static void testColDraw();
};



using Col = Collsion;