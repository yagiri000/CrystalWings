#pragma once

#include <iostream>
#include <deque>
#include <string>

class SaveMgr{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	SaveMgr(const SaveMgr& r) = delete;
	SaveMgr& operator=(const SaveMgr& r) = delete;
	static SaveMgr& get();

	static const int SCORELOGNUM = 5;
	const char *filename;
	std::deque<int> scoreLog;

	void init();
	bool isFileExist(const char *filename);
	void save();
	void load();
	int add(int score);
	int getRankScore(int num);

private:
	SaveMgr();
};