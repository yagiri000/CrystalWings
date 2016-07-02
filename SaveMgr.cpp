#pragma once
#include "SaveMgr.h"

#include <DxLib.h>
#include <iostream>

#include "Abstract.h"
#include "Func.h"



SaveMgr& SaveMgr::get(){
	static SaveMgr inst;
	return inst;
}

//初期化
void SaveMgr::init(){
	if (isFileExist(filename) == 0) {
		save();
	}
	load();
}

//ファイルがあるかどうかを返す関数
bool SaveMgr::isFileExist(const char *filename)
{
	FILE  *fp;

	if (fopen_s(&fp, filename, "r") != 0){
		return 0;
	}
	fclose(fp);
	return 1;
}


void SaveMgr::save(){
	FILE* fp_out;
	errno_t error;

	if ((error = fopen_s(&fp_out, filename, "w")) != 0) {
		exit(1);
	}

	for (int i = 0; i < SCORELOGNUM; i++){
		fprintf(fp_out, "%d ", scoreLog[i]);
	}
	fclose(fp_out);
}

void SaveMgr::load(){
	FILE* fp_in;
	errno_t error;

	if ((error = fopen_s(&fp_in, filename, "r")) != 0) {
		exit(1);
	}

	scoreLog.clear();
	for (int i = 0; i < SCORELOGNUM; i++){
		int tmp;
		fscanf_s(fp_in, "%d ", &tmp);
		scoreLog.emplace_back(tmp);
	}
	fclose(fp_in);
}

//リザルトより、得点を追加
//(順位-1)を返す。N位だったらN-1, 6位以下は-1
int SaveMgr::add(int score){
	scoreLog.emplace_back(score);
	std::sort(scoreLog.begin(), scoreLog.end());
	std::reverse(scoreLog.begin(), scoreLog.end());
	scoreLog.pop_back();
	
	save();

	for (int i = 0; i < SCORELOGNUM; i++){
		if (scoreLog[i] == score){
			return i;
		}
	}
	return -1;
}

//(順位-1)の値を受け取り、対応したスコアを返す
int SaveMgr::getRankScore(int num){
	return scoreLog[num];
}

SaveMgr::SaveMgr() :
filename("data.bny")
{
	for (int i = 0; i < SCORELOGNUM; i++){
		scoreLog.emplace_back(0);
	}
	init();
}

