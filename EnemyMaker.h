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
	int canMakeBulletNum;//�G�𐶐��\�Ȓe�̐�

	void update();
	void draw();
};

