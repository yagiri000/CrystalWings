#include "ScoreMgr.h"
#include "GameMgr.h"
#include "Func.h"
#include "Resource.h"



ScoreMgr::ScoreMgr() :
nowScore(0.0),
scorePlusMin(1000.0),
scorePlus(scorePlusMin),
scorePlusDown(9.0),
killEnemyNum(0),
killEnemyBulletNum(0),
eFrame(0)
{
}

int ScoreMgr::addScoreEnemyKill(){
	int ret = scorePlus;
	nowScore += scorePlus;
	scorePlus += 1000.0;
	killEnemyNum++;
	mgr.statusBar_->addStrLog("DESTROY ENEMY");
	mgr.statusBar_->addStrLog("SCORE +" + std::to_string((int)ret));
	return ret;
}

int ScoreMgr::addScoreBulletKill(){
	int ret = 50.0;
	nowScore += 50.0;
	killEnemyBulletNum++;
	mgr.statusBar_->addStrLog("DESTROY BULLET");
	mgr.statusBar_->addStrLog("SCORE +" + std::to_string((int)ret));
	return ret;
}

void ScoreMgr::update(){
	eFrame++;
	scorePlus -= scorePlusDown;
	scorePlus = std::max<double>(scorePlus, scorePlusMin);
}

void ScoreMgr::draw(){
}