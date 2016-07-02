#include "Result.h"
#include "GameMgr.h"
#include "SaveMgr.h"


ResultBackGround::ResultBackGround()
{
	vel.y = 0.001;
	alpha = 64;
	gHandle = Graph::handle("result_back");
}

//shiftu, shiftv分移動
void ResultBackGround::update(){
	for (int i = 0; i < 6; i++){
		Vert[i].u += vel.x;
		Vert[i].v -= vel.y;
	}
}

void ResultBackGround::draw(){
	SetTextureAddressMode(DX_TEXADDRESS_WRAP);
	SetDrawBlendMode(blendMode, alpha);
	DrawPolygon2D(Vert, 2, gHandle, true);
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
}

IResult::IResult() :
newRank(-1),
eFrame(0),
canToTitleFrame(120),
backGround(),
enemyMaxNum(30),
enemyEffect()
{
	for (int i = 0; i < enemyMaxNum; i++){
		Vector2 pos(Random::FRand(0, ScreenWidth), Random::FRand(0, ScreenHeight));
		enemyEffect.add(std::make_shared<ResultEnemyEffect>(pos));
	}
}

void IResult::setNewRank(int newRank_){
	newRank = newRank_;
}

void IResult::enemyMake(){
	Vector2 pos(Random::FRand(0, 800), -30);
	enemyEffect.add(std::make_shared<ResultEnemyEffect>(pos));
}
void IResult::update(){
	backGround.update();
	enemyEffect.update();
	mgr.effect_.update();
	if (enemyEffect.v.size() < enemyMaxNum){
		enemyMake();
	}
	eFrame++;
	if (eFrame > canToTitleFrame && Input::keydown(KEY_INPUT_Z)){
		mgr.effect_.clearVec();
		shiftScene();
	}
}



ResultFromTitle::ResultFromTitle() :
IResult()
{
	loadData();
	canToTitleFrame = 10;
}

void ResultFromTitle::shiftScene(){
	mgr.sceneMgr_.popBack();
}

void ResultFromTitle::loadData(){
	SaveMgr::get().load();
}

void ResultFromTitle::draw(){
	auto& smgr = mgr.scoreMgr_;
	auto &save = SaveMgr::get();

	backGround.draw();
	enemyEffect.draw();
	mgr.effect_.draw();
	Screen::HSB(0, eFrame, -128, 0);

	int boxColor = 0x000000;
	Draw::centerbox(Vector2(400, 70), Vector2(800, 60), boxColor, 160);
	Draw::centertext_space(Vector2(400, 70 - 30 + 6), 0xFFFFFF, Font::handle("OS50"), 60, "Result", 255);

	int basey = 180;
	Draw::box(Vector2(0, basey), Vector2(800, basey + 180), boxColor, 160);
	Draw::centertext(Vector2(400, basey + 6), 0xFF8800, Font::handle("OS18"), "Ranking", 255);

	

	for (int i = 0; i < 5; i++){
		int y2 = basey + 30 + i * 30;
		Draw::text(Vector2(210, y2), 0xFFFFFF, Font::handle("OS18"),
			std::to_string(i + 1) + " : " + std::to_string(save.getRankScore(i)) + " pt", 255);
		if (newRank == i){
			Draw::righttext(Vector2(200, y2), 0xFF8800, Font::handle("OS18"), "ハイスコア更新！", 128 + 128 * sin(Input::eframe() * 0.1));
		}
	}

	auto toTitleBarAlphaRateEase = [&](){
		int shiftFrame = 60;
		if (eFrame <canToTitleFrame){
			return 0.0;
		}
		else if (eFrame < canToTitleFrame + shiftFrame){
			return ((double)eFrame - canToTitleFrame) / shiftFrame;
		}
		else{
			return 1.0;
		}
	};

	Draw::centerbox(Vector2(400, 556), Vector2(800, 30), boxColor, toTitleBarAlphaRateEase() * 160);
	Draw::centertext(Vector2(400, 556 - 10), 0xFFFFFF, Font::handle("OS18"), "Z TO TITLE", toTitleBarAlphaRateEase() * Func::sinsec(128, 128, 1.0, Input::eframe()));


	//Draw::righttext(Func::GetScreenCenter(), 0xFF8800, Font::handle("OS18"), std::to_string(Input::mousex()), 256);

}


ResultFromMain::ResultFromMain() :
IResult()
{
	loadData();
}

void ResultFromMain::shiftScene(){
	mgr.sceneMgr_.shiftPopBack(std::make_unique<TitleScene>());
}

void ResultFromMain::loadData(){
	setNewRank(SaveMgr::get().add(mgr.scoreMgr_->nowScore));
}

void ResultFromMain::draw(){
	auto& smgr = mgr.scoreMgr_;
	auto &save = SaveMgr::get();

	backGround.draw();
	enemyEffect.draw();
	mgr.effect_.draw();
	Screen::HSB(0, eFrame, -128, 0);

	int boxColor = 0x000000;

	Draw::centerbox(Vector2(400, 70), Vector2(800, 60), boxColor, 160);
	Draw::centertext_space(Vector2(400, 70 - 30 + 6), 0xFFFFFF, Font::handle("OS50"), 60, "Result", 255);

	auto drawstr_box = [&](int y, std::string s1, std::string s2)
	{
		int x1 = 200;
		int x2 = 600;
		int col = 0xFFFFFF;
		Draw::centerbox(Vector2(400, y + 12), Vector2(800, 32), boxColor, 160);
		Draw::text(Vector2(x1, y), col, Font::handle("SegoeUI18"), s1, 255);
		Draw::righttext(Vector2(x2, y), col, Font::handle("OS18"), s2, 255);
	};

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

	int y = 130;
	int yDif = 45;
	drawstr_box(y, "撃破数  :", std::to_string(smgr->killEnemyNum)); y += yDif;
	drawstr_box(y, "敵弾破壊数  :", std::to_string(smgr->killEnemyBulletNum)); y += yDif;
	drawstr_box(y, "耐久時間  :", time_str(smgr->eFrame)); y += yDif;
	drawstr_box(y, "総合スコア  :", std::to_string((int)smgr->nowScore)); y += yDif;

	int yshift = 0;
	Draw::box(Vector2(0, 330), Vector2(800, 505), boxColor, 160);
	Draw::centertext(400, 336 + yshift, 0xFF8800, Font::handle("OS18"), "Ranking", 255);

	for (int i = 0; i < 5; i++){
		int y2 = 360 + i * 30 + yshift;
		Draw::text(Vector2(300, y2), 0xFFFFFF, Font::handle("OS18"),
			std::to_string(i + 1) + " : " + std::to_string(save.getRankScore(i)) + " pt", 255);
		if (newRank == i){
			Draw::righttext(Vector2(290, y2), 0xFF8800, Font::handle("SegoeUI18"), "ハイスコア更新！", 128 + 128 * sin(Input::eframe() * 0.1));
		}
	}

	auto toTitleBarAlphaRateEase = [&](){
		int shiftFrame = 60;
		if (eFrame <canToTitleFrame){
			return 0.0;
		}
		else if (eFrame < canToTitleFrame + shiftFrame){
			return ((double)eFrame - canToTitleFrame) / shiftFrame;
		}
		else{
			return 1.0;
		}
	};

	Draw::centerbox(Vector2(400, 556), Vector2(800, 30), boxColor, toTitleBarAlphaRateEase() * 160);
	Draw::centertext(Vector2(400, 556 - 10), 0xFFFFFF, Font::handle("OS18"), "Z TO TITLE", toTitleBarAlphaRateEase() * Func::sinsec(128, 128, 1.0, Input::eframe()));


	//Draw::righttext(Func::GetScreenCenter(), 0xFF8800, Font::handle("OS18"), std::to_string(Input::mousex()), 256);

}
