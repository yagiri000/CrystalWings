#pragma once
#include <iostream>

#include "Effects.h"
#include "Abstract.h"
#include "Screen.h"
#include "Easing.h"
#include "EffectFactory.h"
#include "Enemy.h"
#include "Player.h"
#include "ScoreMgr.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"
#include "BackGround.h"
#include "EnemyMaker.h"
#include "Scene.h"
#include "StatusBar.h"

class GameMgr{
public:
	GameMgr(const GameMgr& r) = delete;//ÉRÉsÅ[ã÷é~
	GameMgr& operator=(const GameMgr& r) = delete;//ë„ì¸ã÷é~
	static GameMgr& get();

	bool gameEndFlag;
	bool screenInvertFlag;

	std::shared_ptr<Player> player_;
	std::shared_ptr<EnemyMaker> enemyMaker_;
	std::shared_ptr<ScoreMgr> scoreMgr_;
	std::shared_ptr<StatusBar> statusBar_;
	std::shared_ptr<BackGround> backGround_;
	Mgr<IEffect> effect_;
	Mgr<IEnemy> enemy_;
	Mgr<IEnemyBullet> eBullet_;
	Mgr<IPlayerBullet> pBullet_;

	SceneMgr sceneMgr_;
	
	void update();
	void draw();
	void draw2();

	void init();
	void loadResource();
	double getLevel();

private:
	GameMgr();
};


extern GameMgr& mgr;