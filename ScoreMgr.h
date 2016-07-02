#pragma once

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <functional>

#include "Abstract.h"
#include "Vector2.h"
#include "Collision.h"

class ScoreMgr
{
public:
	ScoreMgr();
	double nowScore;
	double scorePlusMin;
	double scorePlus;
	double scorePlusDown;
	lint killEnemyNum;
	lint killEnemyBulletNum;
	lint eFrame;

	int addScoreEnemyKill();
	int addScoreBulletKill();
	void update();
	void draw();
};

