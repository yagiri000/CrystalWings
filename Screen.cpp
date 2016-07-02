#include "Screen.h"

#include "DxLib.h"
#include <string>
#include "Func.h"

Screen& Screen::get(){
	static Screen inst;
	return inst;
}

// �K�E�X�t�B���^�[���{��
void Screen::setTransition(int frame){
	get().transitionFrame = frame;
	get().transitionFrameMax = frame;
}

// �K�E�X�t�B���^�[���{��
void Screen::Gauss(int pal_1, int pal_2){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GAUSS, pal_1, pal_2);
}
// HSB�t�B���^�[���{��
void Screen::HSB(int type, int hue, int saturation, int bright){
	if (type == 0){
		hue %= 360;
		if (hue < -180){
			hue += 360;
		}
		if (hue > 180){
			hue -= 360;
		}
	}
	else{
		hue %= 360;
		if (hue < 0){
			hue += 360;
		}
	}
	/*hue += 180;
	hue = (hue % 360) - 180;
	if (hue < -180){
		hue += 360;
	}*/
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_HSB, type, hue, saturation, bright);
}

// �K�����]�t�B���^�[���{��
void Screen::Invert(){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_INVERT);
}

// Level�t�B���^�[���{��
void Screen::Level(int min, int max, int gamma, int afterMin, int afterMax){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_LEVEL, min, max, gamma, afterMin, afterMax);
}

// �O���f�[�V�����}�b�v�t�B���^�[���{��
void Screen::GradiendMap(int handle){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GRADIENT_MAP, handle, FALSE);
}

//�`��J�n
void Screen::DrawStart(){
	SetDrawScreen(get().mainScreen);
	ClearDrawScreen();
}

//�V�F�[�_�[�Ƃ��K�p���鎞�p
void Screen::SetDrawScreenSub(){
	SetDrawScreen(get().subScreen);
}

//�V�F�[�_�[�Ƃ��K�p�������Ɨp
void Screen::SetDrawScreenMain(){
	SetDrawScreen(get().mainScreen);
}

//�`��I���E�t���b�v
void Screen::DrawEnd(){
	if (get().transitionFrame-- >= 0){
		if (get().transitionFrameMax != 0){
			double rate = (double)get().transitionFrame / get().transitionFrameMax;
			Screen::Gauss(8, 600.0 * rate);
			double pal = -255.0 * rate;
			Screen::HSB(0, 0, pal, pal);
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (get().screenShakeFrame-- >= 0){
		double dx, dy;
		Random::RandInCircle(get().screenShakeDistance, dx, dy);
		DrawGraph(dx, dy, get().mainScreen, FALSE);
	}
	else{
		DrawGraph(0, 0, get().mainScreen, FALSE);
	}


	ScreenFlip();
}

//�X�N���[���h���ݒ�
void Screen::SetShake(int frame, int distance){
	get().screenShakeFrame = frame;
	get().screenShakeDistance = distance;
}

//�c�����C���[�Ɍ��݂̃��C���[���R�s�[
void Screen::SetAfterImageScreen(){
	SetDrawScreen(get().afterImageScreen);
	ClearDrawScreen();
	GraphFilterBlt(get().mainScreen, get().afterImageScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
	get().afterImageAlpha = 255;
	SetDrawScreen(get().mainScreen);
}

//�c�����C���[��`��
void Screen::DrawAfterImageScreen(){
	if (get().afterImageAlpha >= 0){
		GraphFilter(get().afterImageScreen, DX_GRAPH_FILTER_GAUSS, 8, 100);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, get().afterImageAlpha);
		DrawGraph(0, 0, get().afterImageScreen, TRUE);
		get().afterImageAlpha -= 5;
	}
}

Screen::Screen() :
width(1024),
height(1024),
afterImageAlpha(0),
screenShakeFrame(0),
screenShakeDistance(0),
transitionFrame(0),
transitionFrameMax(0)
{
	init();
}

void Screen::init(){
	//�V���ɃX�N���[�����쐬
	mainScreen = MakeScreen(width, height, 1);
	afterImageScreen = MakeScreen(width, height, 1);
	tmpScreen = MakeScreen(width, height, 1);
	subScreen = MakeScreen(width, height, 1);
}


