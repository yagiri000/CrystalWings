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
	SetBackgroundColor(255, 255, 255);//�w�i���ɐݒ�
	SetOutApplicationLogValidFlag(FALSE);//log�𐶐����Ȃ��悤�ɐݒ�
	if (DxLib_Init() == 1){ return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

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

		Screen::DrawStart(); //�`��J�n, ClearScreen
		{
			GameMgr::get().draw();
			GameMgr::get().draw2();
		}
		Screen::DrawEnd(); //�`��I��, ScreenFlip

		//�t���O��true�Ȃ�Q�[���I��
		if (mgr.gameEndFlag){
			break;
		}
	}


	DxLib_End();
	return 0;
}

