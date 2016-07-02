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

//������
void SaveMgr::init(){
	if (isFileExist(filename) == 0) {
		save();
	}
	load();
}

//�t�@�C�������邩�ǂ�����Ԃ��֐�
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

//���U���g���A���_��ǉ�
//(����-1)��Ԃ��BN�ʂ�������N-1, 6�ʈȉ���-1
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

//(����-1)�̒l���󂯎��A�Ή������X�R�A��Ԃ�
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

