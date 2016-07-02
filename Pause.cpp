#include "Pause.h"
#include "GameMgr.h"
#include "Easing.h"

Pause::Pause() :
eFrame(0),
nowSelect(0),
nowSelectMax(1)
{
}


void Pause::selectUpdate(){
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

}

void Pause::pushKey(){
	if (Input::keydown(KEY_INPUT_ESCAPE)){
		//自分自身のシーンをポップ（メインに戻る）
		mgr.sceneMgr_.popBack();
		Sound::playone("title_out");
	}

	if (Input::keydown(KEY_INPUT_Z)){
		if (nowSelect == 0){
			//自分自身のシーンをポップ（メインに戻る）
			mgr.sceneMgr_.popBack();
			Sound::playone("title_out");
		}
		else if (nowSelect == 1){
			//スタックにPauseSelectToTitleシーンを重ねる
			mgr.sceneMgr_.add(std::make_unique<PauseSelectScene>());
			Sound::playone("title_out");
		}
	}
}

void Pause::update(){
	eFrame++;
	selectUpdate();
	pushKey();
}

void Pause::draw(){
	mgr.backGround_->draw();
	mgr.enemy_.draw();
	mgr.player_->draw();
	mgr.eBullet_.draw();
	mgr.pBullet_.draw();
	mgr.enemyMaker_->draw();
	mgr.effect_.draw();
	mgr.scoreMgr_->draw();
	mgr.statusBar_->draw();

	

	Draw::box(Vector2(0, 0), Vector2(ScreenWidth, ScreenHeight), 0x000000, 128);
	Draw::centertext_space(Func::GetScreenCenter() + Vector2(0, -60), 0xFFFFFF, font("OS50"), 
		Ease::sinOut(eFrame, 20, 100, 40), "PAUSE", 255);

	for (int i = 0; i < 2; i++){
		Vector2 pos(ScreenWidth / 2, 400 + 60 * i);
		Draw::center(pos, GraphDiv::handle("pause_str", i), 255);
		if (i == nowSelect){
			Draw::center(pos, GraphDiv::handle("pause_str_selected", i), Func::sinsec(200, 56, 1.0, eFrame));
		}
	}
}


PauseSelect::PauseSelect() :
eFrame(0),
nowSelect(1),
nowSelectMax(1)
{
}


void PauseSelect::selectUpdate(){
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

}

void PauseSelect::pushKey(){
	if (Input::keydown(KEY_INPUT_Z) || Input::keydown(KEY_INPUT_SPACE)){
		if (nowSelect == 0){
			//自分自身のシーンをポップ（Pauseに戻る）
			Sound::playone("title_out");
			mgr.sceneMgr_.shiftPopAll(std::make_unique<TitleScene>());
		}
		else if (nowSelect == 1){
			Sound::playone("title_out");
			//スタックにPauseSelectToTitleシーンを重ねる
			mgr.sceneMgr_.popBack();
		}
	}
}

void PauseSelect::update(){
	eFrame++;
	selectUpdate();
	pushKey();
}

void PauseSelect::draw(){
	mgr.backGround_->draw();
	mgr.enemy_.draw();
	mgr.player_->draw();
	mgr.eBullet_.draw();
	mgr.pBullet_.draw();
	mgr.enemyMaker_->draw();
	mgr.effect_.draw();
	mgr.scoreMgr_->draw();
	mgr.statusBar_->draw();
	Draw::box(Vector2(0, 0), Vector2(ScreenWidth, ScreenHeight), 0x000000, 128);
	Draw::centertext_space(Func::GetScreenCenter() + Vector2(0, -60), 0xFFFFFF, font("OS50"), 
		40.0, "PAUSE", 255);
	Draw::centertext_space(Func::GetScreenCenter() + Vector2(0, -10), 0xFFFFFF, font("OS50"), 
		Ease::sinOut(eFrame, 20, 100, 40), "Return Title?", 255);

	for (int i = 0; i < 2; i++){
		Vector2 pos(ScreenWidth / 2, 400 + 60 * i);
		Draw::center(pos, GraphDiv::handle("pause_str", i+2), 255);
		if (i == nowSelect){
			Draw::center(pos, GraphDiv::handle("pause_str_selected", i + 2), Func::sinsec(200, 56, 1.0, eFrame));
		}
	}
}