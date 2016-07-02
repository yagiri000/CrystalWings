#pragma once

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <functional>

#include "Abstract.h"
#include "Vector2.h"
#include "Collision.h"

class NumLogGraph : public IObject{
public:
	NumLogGraph(std::function<int()>);
	std::function<int()> retNumFunc;
	static const int NumLogGraphNum = 150;
	std::deque<int> logDeque;
	int color;
	void update();
	void draw();
};

class StrLog{
public:
	StrLog();
	std::deque<std::string> strLog;
	Vector2 startPos;
	double addDifY;
	double addDifYMoveRate;
	int difY;
	int logNumMax;
	int fontColor;
	int fontHandle;
	int alpha;
	void add(const std::string &str);
	void update();
	void draw();
};

class StatusBar
{
public:
	StatusBar();

	lint eFrame;
	StrLog strLog;
	Mgr<NumLogGraph> numLogGraphVec;

	void addStrLog(const std::string &str);
	void update();
	void draw();
};

