#pragma once

#include "myglobal.h"
#include <deque>
#include <string>
#include <vector>
#include <memory>
#include "BackGround.h"
#include "Enemy.h"


class Title
{
public:
	Title();

	lint eFrame;
	int nowSelect;
	int nowSelectMax;

	void effectMake();
	void update();
	void draw();
};


