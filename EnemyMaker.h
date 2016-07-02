#pragma once


#include "Abstract.h"


class EnemyMaker : public IObject
{
public:
	EnemyMaker();

	int cool;
	int rate;
	int canCool;
	int canRate;
	int canMakeBulletNum;//敵を生成可能な弾の数

	void update();
	void draw();
};

