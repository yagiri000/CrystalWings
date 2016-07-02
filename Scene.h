#pragma once

#include <vector>
#include <stack>
#include <memory>

#include <sstream>
#include <cassert>
#include <crtdbg.h>

#include "myglobal.h"

#include "Title.h"
#include "Result.h"
#include "Pause.h"


//シーン基底クラス
//これを継承して使う
class IScene
{
protected:
	int eFrame;
public:
	IScene();
	virtual void update();
	int getTimer();
	void setTimer(int x);
	virtual void draw() = 0;
};


//シーン管理クラス
//stack + unique_ptrで管理
class SceneMgr
{
public:
	bool exit;
	std::stack<std::unique_ptr<IScene>> scene_stack;
	std::unique_ptr<IScene> next;
	std::unique_ptr<IScene> nextAllPop;
	bool isPopFront;

	SceneMgr();
	SceneMgr(std::unique_ptr<IScene> p);

	void add(std::unique_ptr<IScene> new_object);
	void shiftPopBack(std::unique_ptr<IScene> new_object);
	void shiftPopAll(std::unique_ptr<IScene> new_object);
	void popBack();
	void update();
	void draw();
	void setEnd(bool end);

private:
	void pop();
};


class PreTitleScene : public IScene{
public:
	PreTitleScene();
	virtual void update();
	virtual	void draw();
};


class TitleScene : public IScene{
public:
	TitleScene();
	Title title;
	virtual void update();
	virtual	void draw();
};

class ResultFromTitleScene : public IScene{
public:
	ResultFromTitleScene();
	ResultFromTitle result;
	virtual void update();
	virtual void draw();
};


class TitleToMainScene : public IScene{
public:
	int nextSceneFrame;
	TitleToMainScene();
	virtual void update();
	virtual	void draw();
};


class MainScene : public IScene{
public:
	MainScene();
	virtual void update();
	virtual void draw();
};


class PauseScene : public IScene{
public:
	PauseScene();
	Pause pause;
	virtual void update();
	virtual void draw();
};


class PauseSelectScene : public IScene{
public:
	PauseSelectScene();
	PauseSelect pause;
	virtual void update();
	virtual void draw();
};

class MainToResult : public IScene{
public:
	MainToResult();
	int shift1;
	int shift2;
	virtual void update();
	virtual void draw();
};

class ResultFromMainScene : public IScene{
public:
	ResultFromMainScene();
	ResultFromMain result;
	virtual void update();
	virtual void draw();
};
