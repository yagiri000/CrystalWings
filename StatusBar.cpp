#include "StatusBar.h"
#include "GameMgr.h"
#include "Func.h"
#include "Resource.h"
#include "SaveMgr.h"

NumLogGraph::NumLogGraph(std::function<int()> f) :
retNumFunc(f),
color(Func::HSVtoRGB(Random::Rand(360), 255, 255))
{
	for (int i = 0; i < NumLogGraphNum; i++){
		logDeque.emplace_front(0);
	}
}

void NumLogGraph::update(){
	logDeque.pop_back();
	logDeque.emplace_front(retNumFunc());
}

void NumLogGraph::draw(){
	for (auto i = logDeque.begin(); i < logDeque.end(); i++){
		int num = i - logDeque.begin();
		Draw::line(Vector2(num, ScreenHeight), Vector2(num, ScreenHeight - (*i)), color, 128);
	}
}


StrLog::StrLog() :
difY(-12),
logNumMax((ScreenHeight - StatusBarWidth) / abs(difY)),
startPos(ScreenWidth - StatusBarWidth + 12, ScreenHeight - 14 - StatusBarWidth),
addDifY(0),
addDifYMoveRate(0.1),
fontColor(0xFFFFFF),
fontHandle(font("OS12")),
alpha(255)
{

}

void StrLog::add(const std::string &str){
	strLog.push_front(str);
	addDifY += -difY;
}

void StrLog::update(){
	while (strLog.size() > logNumMax){
		strLog.pop_back();
	}
	Func::moverate(addDifY, 0, addDifYMoveRate);

}

void StrLog::draw(){
	Vector2 pos = startPos;
	pos.y += addDifY;
	int hue = 0;
	double alphaf = 255.0;
	for (auto &i = strLog.begin(); i < strLog.end(); i++){
		if (pos.y < ScreenHeight - StatusBarWidth){
			Draw::text(pos, fontColor, fontHandle, *i, alphaf);
		}
		pos.y += difY;
		alphaf -= 255.0 / logNumMax;
	}
}


StatusBar::StatusBar() :
eFrame(0),
strLog(),
numLogGraphVec()
{
	numLogGraphVec.add(std::make_shared<NumLogGraph>([&](){
		return (int)(mgr.scoreMgr_->scorePlus * 0.01);
	}));
	numLogGraphVec.add(std::make_shared<NumLogGraph>([](){
		return (int)(mgr.effect_.v.size());
	}));
	numLogGraphVec.add(std::make_shared<NumLogGraph>([](){
		return (int)(mgr.eBullet_.v.size());
	}));

}

void StatusBar::addStrLog(const std::string &str){
	strLog.add(str);
}

void StatusBar::update(){
	eFrame++;
	strLog.update();
	numLogGraphVec.update();
}

void StatusBar::draw(){
	numLogGraphVec.draw();

	auto &score = *(mgr.scoreMgr_);


	auto time_str = [&](int frame){
		int sec = frame / 60;
		if ((sec % 60) < 10){
			return std::to_string((int)(sec / 60)) +
				":0" +
				std::to_string((int)(sec % 60));
		}
		else{
			return std::to_string((int)(sec / 60)) +
				":" +
				std::to_string((int)(sec % 60));
		}
	};

	int marge = StatusBarWidth;
	int alpha = 128;
	int color = 0x000000;
	int margeForShake = 120;


	Draw::box(Vector2(0, 0), Vector2(marge, ScreenHeight + margeForShake), color, alpha);
	Draw::box(Vector2(ScreenWidth - marge, 0), Vector2(ScreenWidth, ScreenHeight + margeForShake), color, alpha);
	Vector2 pos(15, 20);
	Vector2 dPos(0, 35);
	Vector2 dPos2(0, 16);

	int hiScore = std::max<int>((int)score.nowScore, SaveMgr::get().getRankScore(0));
	Draw::text(pos, 0xFFFFFF, font("OS14"), "Hi-Score:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(hiScore), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "Score:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string((int)score.nowScore), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "Player:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "@" + std::to_string(mgr.player_->remainingLives), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "Bomb:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "@" + std::to_string(mgr.player_->getBombNum()), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "Time:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), time_str(score.eFrame), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "D-Enemy:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(score.killEnemyNum), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS14"), "D-Bullet:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(score.killEnemyBulletNum), 255); pos += dPos;


	/*
	Draw::text(pos, 0xFFFFFF, font("OS18"), "EBulletNum:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(mgr.eBullet_.v.size()), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "ScorePlus:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string((int)score.scorePlus), 255); pos += dPos;

	Draw::text(pos, 0xFFFFFF, font("OS18"), "EnemyNum:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(mgr.enemy_.v.size()), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "EBulletNum:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(mgr.eBullet_.v.size()), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "CanBullet:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), std::to_string(mgr.enemyMaker_->canMakeBulletNum), 255); pos += dPos;
	Draw::text(pos, 0xFFFFFF, font("OS18"), "PlayerState:", 255); pos += dPos2;
	Draw::text(pos, 0xFFFFFF, font("OS18"), mgr.player_->getStateString(), 255); pos += dPos;
	*/

	strLog.draw();

	Draw::normal(Vector2(ScreenWidth - StatusBarWidth, ScreenHeight - StatusBarWidth), Graph::handle("mini_title"), 255);
	//Draw::normal(Vector2(ScreenWidth - StatusBarWidth, 0), Graph::handle("mini_title"), 255);
}