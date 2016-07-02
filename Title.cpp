#include "Title.h"
#include "GameMgr.h"

Title::Title() :
eFrame(0),
nowSelect(0),
nowSelectMax(2)
{
}

void Title::effectMake(){
	if (Random::RandBool(0.3)){
		eff::make(Vector2(-80, Random::FRand(ScreenHeight)), "TitleEf");
	}
}

void Title::update(){
	eFrame++;
	effectMake();

	int preSelect = nowSelect;
	if (Input::keydown(KEY_INPUT_UP)){
		nowSelect--;
		nowSelect = std::max<int>(nowSelect, 0);
	}
	if (Input::keydown(KEY_INPUT_DOWN)){
		nowSelect++;
		nowSelect = std::min<int>(nowSelect, nowSelectMax);
	}

	if (preSelect != nowSelect){
		Sound::playone("title_cursor_move");
	}

	if (Input::keydown(KEY_INPUT_Z) || Input::keydown(KEY_INPUT_SPACE)){
		if (nowSelect == 0){
			Sound::playone("title_out");
			mgr.sceneMgr_.shiftPopBack(std::make_unique<TitleToMainScene>());
		}
		else if (nowSelect == 1){
			Sound::playone("title_out");
			mgr.sceneMgr_.add(std::make_unique<ResultFromTitleScene>());
		}
		else if (nowSelect == 2){
			Sound::playone("title_out");
			mgr.gameEndFlag = true;
		}
	}
}

void Title::draw(){
	Draw::normal(Vector2(0, 0), Graph::handle("title"), 255);
	for (int i = 0; i < 3; i++){
		Vector2 pos(ScreenWidth / 2, 400 + 60 * i);
		Draw::center(pos, GraphDiv::handle("title_str", i), 255);
		if (i == nowSelect){
			Draw::center(pos, GraphDiv::handle("title_str_selected", i), Func::sinsec(200, 56, 1.0, eFrame));
		}
	}
}