#pragma once

#include <DxLib.h>
#include <iostream>

#include "myglobal.h"
#include "Resource.h"
#include "Func.h"
#include "GameMgr.h"
#include "Screen.h"
#include "Effects.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowIconID(101);
	SetMainWindowText("CRYSTAL WINGS");
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	SetBackgroundColor(255, 255, 255);//背景白に設定
	SetOutApplicationLogValidFlag(FALSE);//logを生成しないように設定
	if (DxLib_Init() == 1){ return -1; }//初期化に失敗時にエラーを吐かせて終了

	Input::get();
	Screen::get();
	GameMgr::get().loadResource();


	while( ProcessMessage() == 0)
	{
		GameMgr::get().update();

#if DEBUG == 1
		if (Input::keydown(KEY_INPUT_A)){

		}
#endif

		Screen::DrawStart(); //描画開始, ClearScreen
		{
			GameMgr::get().draw();
			GameMgr::get().draw2();
		}
		Screen::DrawEnd(); //描画終了, ScreenFlip

		//フラグがtrueならゲーム終了
		if (mgr.gameEndFlag){
			break;
		}
	}


	DxLib_End();
	return 0;
}

