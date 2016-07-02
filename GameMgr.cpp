#include "GameMgr.h"

GameMgr& mgr = GameMgr::get();

GameMgr& GameMgr::get(){
	static GameMgr inst;
	return inst;
}

void GameMgr::update(){
	Input::update();//キー更新
	Sound::update();

	sceneMgr_.update();
}


void GameMgr::draw(){
	sceneMgr_.draw();
}

void GameMgr::draw2(){
}

void GameMgr::init(){
	player_ = std::make_shared<Player>();
	enemyMaker_ = std::make_shared<EnemyMaker>();
	scoreMgr_ = std::make_shared<ScoreMgr>();
	statusBar_ = std::make_shared<StatusBar>();
	backGround_ = std::make_shared<BackGround>(); 
	effect_.clearVec();
	enemy_.clearVec();
	eBullet_.clearVec();
	pBullet_.clearVec();
}

void GameMgr::loadResource(){
	GraphB::get().load();
	GraphHue::get().load();
	Graph::get().load();
	GraphDiv::get().load();
	Font::get().load();
	Sound::get().load();
}


double GameMgr::getLevel(){
	return 1.0;
}

GameMgr::GameMgr() :
gameEndFlag(false),
screenInvertFlag(false),
sceneMgr_(std::make_unique<PreTitleScene>())
{
};