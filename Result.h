#pragma once
#include "myglobal.h"
#include <deque>
#include <string>
#include <vector>
#include <memory>
#include "BackGround.h"
#include "Enemy.h"


class ResultBackGround : public BackGroundParts{
public:
	ResultBackGround();
	virtual void update();
	virtual void draw();
};


class IResult{
public:
	IResult();
	Mgr<IEnemy> enemyEffect;
	ResultBackGround backGround;
	int newRank;
	lint eFrame;
	const int enemyMaxNum;
	int canToTitleFrame;
	void setNewRank(int newRank_);
	void enemyMake();
	virtual void update();
	virtual void shiftScene() = 0;
	virtual void loadData() = 0;
	virtual void draw() = 0;
};

class ResultFromTitle : public IResult{
public:
	ResultFromTitle();
	virtual void shiftScene();
	virtual void loadData();
	virtual void draw();
};

class ResultFromMain : public IResult{
public:
	ResultFromMain();
	virtual void shiftScene();
	virtual void loadData();
	virtual void draw();
};

