#pragma once

#include "myglobal.h"
#include <deque>
#include <string>
#include <vector>
#include <memory>
#include "BackGround.h"
#include "Enemy.h"


class Pause
{
public:
	Pause();

	lint eFrame;
	int nowSelect;
	int nowSelectMax;

	void selectUpdate();
	void pushKey();
	void update();
	void draw();
};


class PauseSelect
{
public:
	PauseSelect();

	lint eFrame;
	int nowSelect;
	int nowSelectMax;

	void selectUpdate();
	void pushKey();
	void update();
	void draw();
};