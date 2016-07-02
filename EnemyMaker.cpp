#include "GameMgr.h"
#include "EnemyMaker.h"


EnemyMaker::EnemyMaker():
cool(180),
rate(60),
canCool(0),
canRate(90),
canMakeBulletNum(10)
{
}

void EnemyMaker::update(){
	if (Func::coolcount(canCool)){
		canCool = canRate;
		canMakeBulletNum++;
	}
	if (Func::coolcount(cool) && mgr.eBullet_.v.size() < canMakeBulletNum){
		cool = rate;
		mgr.enemy_.add(std::make_shared<Enemy_>(Random::RandScreenEdge()));
	}
}

void EnemyMaker::draw(){

}
