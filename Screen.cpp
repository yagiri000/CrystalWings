#include "Screen.h"

#include "DxLib.h"
#include <string>
#include "Func.h"

Screen& Screen::get(){
	static Screen inst;
	return inst;
}

// ガウスフィルターを施す
void Screen::setTransition(int frame){
	get().transitionFrame = frame;
	get().transitionFrameMax = frame;
}

// ガウスフィルターを施す
void Screen::Gauss(int pal_1, int pal_2){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GAUSS, pal_1, pal_2);
}
// HSBフィルターを施す
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

// 階調反転フィルターを施す
void Screen::Invert(){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_INVERT);
}

// Levelフィルターを施す
void Screen::Level(int min, int max, int gamma, int afterMin, int afterMax){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_LEVEL, min, max, gamma, afterMin, afterMax);
}

// グラデーションマップフィルターを施す
void Screen::GradiendMap(int handle){
	GraphFilter(get().mainScreen, DX_GRAPH_FILTER_GRADIENT_MAP, handle, FALSE);
}

//描画開始
void Screen::DrawStart(){
	SetDrawScreen(get().mainScreen);
	ClearDrawScreen();
}

//シェーダーとか適用する時用
void Screen::SetDrawScreenSub(){
	SetDrawScreen(get().subScreen);
}

//シェーダーとか適用したあと用
void Screen::SetDrawScreenMain(){
	SetDrawScreen(get().mainScreen);
}

//描画終了・フリップ
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

//スクリーン揺れを設定
void Screen::SetShake(int frame, int distance){
	get().screenShakeFrame = frame;
	get().screenShakeDistance = distance;
}

//残像レイヤーに現在のレイヤーをコピー
void Screen::SetAfterImageScreen(){
	SetDrawScreen(get().afterImageScreen);
	ClearDrawScreen();
	GraphFilterBlt(get().mainScreen, get().afterImageScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
	get().afterImageAlpha = 255;
	SetDrawScreen(get().mainScreen);
}

//残像レイヤーを描画
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
	//新たにスクリーンを作成
	mainScreen = MakeScreen(width, height, 1);
	afterImageScreen = MakeScreen(width, height, 1);
	tmpScreen = MakeScreen(width, height, 1);
	subScreen = MakeScreen(width, height, 1);
}


