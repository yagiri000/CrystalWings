#include "Scene.h"
#include "Func.h"
#include "GameMgr.h"
#include "SaveMgr.h"

IScene::IScene():
eFrame(0)
{
}

void IScene::update(){ 
	eFrame++; 
}

int IScene::getTimer(){ 
	return eFrame; 
}

void IScene::setTimer(int x){
	eFrame = x; 
}


SceneMgr::SceneMgr() : 
exit(false),
isPopFront(false)
{
}

SceneMgr::SceneMgr(std::unique_ptr<IScene> p) : 
exit(false),
isPopFront(false)
{
	add(std::move(p));
}

//スタックにシーンオブジェクトを追加
void SceneMgr::add(std::unique_ptr< IScene > new_object)
{
	scene_stack.push(std::move(new_object));
}

//一番上のシーンを破棄し、新たなシーンを入れる
void SceneMgr::shiftPopBack(std::unique_ptr< IScene > new_object){
	next = std::move(new_object);
}

//一番上のシーンを破棄し、新たなシーンを入れる
void SceneMgr::shiftPopAll(std::unique_ptr< IScene > new_object){
	nextAllPop = std::move(new_object);
}

//一番上のシーンを破棄
void SceneMgr::popBack()
{
	isPopFront = true;
}

//一番上のシーンを破棄
void SceneMgr::pop()
{
	scene_stack.pop();
}

void SceneMgr::update()
{
	assert(!scene_stack.empty() && "update() called when scene stack empty");
	
	scene_stack.top()->update();

	if (isPopFront){
		scene_stack.pop();
		isPopFront = false;
	}

	//shift関数が呼ばれnextAllPopに何か入っていれば、すべてのシーンを破棄して次のシーンに入れ替える
	if (nextAllPop != nullptr){
		while (scene_stack.size() == 0){
			scene_stack.pop();
		}
		scene_stack.push(std::move(nextAllPop));
	}

	//shift関数が呼ばれnextに何か入っていれば、現在のシーンを破棄して次のシーンに入れ替える
	if (next != nullptr){
		scene_stack.pop();
		scene_stack.push(std::move(next));
	}
}

void SceneMgr::draw()
{
	assert(!scene_stack.empty() && "update() called when scene stack empty");
	scene_stack.top()->draw();
}

void SceneMgr::setEnd(bool end)
{
	exit = end;
}




PreTitleScene::PreTitleScene(){
}

void PreTitleScene::update(){
	eFrame++;
	//PreTitleSceneはダミーのシーンなので、いきなり次のシーンに飛ぶ
	mgr.sceneMgr_.shiftPopBack(std::make_unique<TitleScene>());
}

void PreTitleScene::draw(){
}




TitleScene::TitleScene():
title()
{
	mgr.effect_.clearVec();
	Sound::playbgm("title_bgm");
}

void TitleScene::update(){
	eFrame++;
	title.update();
	mgr.effect_.update();

#if DEBUG == 2
	//////////////////////////////////////////////////
	Screen::setTransition(60);
	mgr.sceneMgr_.shiftPopBack(std::make_unique<MainScene>());
	//////////////////////////////////////////////////
#endif

}

void TitleScene::draw(){
	mgr.effect_.draw();
	title.draw();
}




ResultFromTitleScene::ResultFromTitleScene() :
result()
{
	mgr.effect_.clearVec();
}

void ResultFromTitleScene::update(){
	eFrame++;
	result.update();
}

void ResultFromTitleScene::draw(){
	result.draw();
}


TitleToMainScene::TitleToMainScene():
nextSceneFrame(30)
{
}

void TitleToMainScene::update(){
	eFrame++;
	if (eFrame > nextSceneFrame){
		//次のシーンに飛ぶ
		Screen::setTransition(60);
		mgr.sceneMgr_.shiftPopBack( std::make_unique<MainScene>());
	}
}

void TitleToMainScene::draw(){
	Draw::normal(Vector2(0, 0), Graph::handle("title"), 255);
	Screen::Gauss(8, eFrame * 20 - 300);
	Draw::box(Vector2(0, 0), Vector2(ScreenWidth, ScreenHeight), 0x000000, 255.0 * eFrame / nextSceneFrame);
}




MainScene::MainScene(){
	Sound::playbgm("main_bgm");
	mgr.init();
}

void MainScene::update(){


#if DEBUG == 2
	/////!!!!!!!!!!!!!!!!!!!
	if (Input::keydown(KEY_INPUT_S)){
		mgr.sceneMgr_.shiftPopBack(std::make_unique<MainToResult>());
	}
	if (Input::keydown(KEY_INPUT_1)){
		mgr.sceneMgr_.shiftPopBack(std::make_unique<TitleScene>());
	}
	/////!!!!!!!!!!!!!!!!!!!!
#endif

	if (mgr.player_->remainingLives <= 0){
		mgr.sceneMgr_.shiftPopBack(std::make_unique<MainToResult>());
	}

	eFrame++;
	mgr.backGround_->update();
	mgr.enemy_.update();
	mgr.player_->update();
	mgr.eBullet_.update();
	mgr.pBullet_.update();
	mgr.enemyMaker_->update();
	mgr.effect_.update();
	mgr.scoreMgr_->update();
	mgr.statusBar_->update();


	if (Input::keydown(KEY_INPUT_ESCAPE)){
		Sound::playone("pause_in");
		mgr.sceneMgr_.add(std::make_unique<PauseScene>());
	}
}

void MainScene::draw(){
	mgr.backGround_->draw();
	mgr.enemy_.draw();
	mgr.player_->draw();
	mgr.eBullet_.draw();
	mgr.pBullet_.draw();
	mgr.enemyMaker_->draw();
	mgr.effect_.draw();
	mgr.scoreMgr_->draw();
	if (mgr.screenInvertFlag){
		Screen::Invert();
		mgr.screenInvertFlag = false;
	}

	mgr.statusBar_->draw();
}



PauseScene::PauseScene() :
pause()
{
}

void PauseScene::update(){
	eFrame++;
	pause.update();
}

void PauseScene::draw(){
	pause.draw();
}



PauseSelectScene::PauseSelectScene() :
pause()
{
}

void PauseSelectScene::update(){
	eFrame++;
	pause.update();
}

void PauseSelectScene::draw(){
	pause.draw();
}




MainToResult::MainToResult() :
shift1(180),
shift2(30)
{
}

void MainToResult::update(){
	eFrame++;

	if (eFrame > shift1 + shift2){
		Screen::setTransition(60);
		mgr.sceneMgr_.shiftPopBack(std::make_unique<ResultFromMainScene>());
	}

	mgr.backGround_->update();
	mgr.enemy_.update();
	mgr.eBullet_.update();
	mgr.pBullet_.update();
	mgr.enemyMaker_->update();
	mgr.effect_.update();
	mgr.scoreMgr_->update();
	mgr.statusBar_->update();
}

void MainToResult::draw(){
	mgr.backGround_->draw();
	mgr.enemy_.draw();
	mgr.eBullet_.draw();
	mgr.pBullet_.draw();
	mgr.enemyMaker_->draw();
	mgr.effect_.draw();
	mgr.scoreMgr_->draw();
	mgr.statusBar_->draw();

	Draw::centerbox(Func::GetScreenCenter(), Vector2(ScreenWidth, 60), 0x000000, std::min<int>(eFrame, 120));
	Draw::centertext_space(Func::GetScreenCenter() + Vector2(0, -25), 0xFFFFFF, font("OS50"), 
		Ease::sinOut(eFrame, 60, 100, 40), "GAME OVER", 255);

	if (eFrame < shift1){

	}
	else{
		int frame = eFrame - shift1;
		Screen::Gauss(8, frame * 20);
		int pal = -frame * 8;
		Screen::HSB(0, 0, pal, pal);
	}
}



ResultFromMainScene::ResultFromMainScene() :
result()
{
	mgr.effect_.clearVec();
}

void ResultFromMainScene::update(){
	eFrame++;
	result.update();
}


void ResultFromMainScene::draw(){
	result.draw();
}
