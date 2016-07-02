#pragma once

#include <string>

class Screen{
public:
	//シングルトン
	Screen& operator=(const Screen& a) = delete;
	Screen(const Screen& a) = delete;
	static Screen& get();

	//スクリーンサイズ
	const int width;
	const int height;

	int afterImageAlpha;
	int screenShakeFrame;	//0の間はスクリーンは揺れない
	int screenShakeDistance;
	int transitionFrame;
	int transitionFrameMax;

	//スクリーン
	int mainScreen;		//主にこれに描画する
	int afterImageScreen;//残像用レイヤー
	int tmpScreen;
	int subScreen; //シェーダー適用用

	static void setTransition(int frame);

	// ガウスフィルターを施す
	static void Gauss(int pal_1 = 8, int pal_2 = 1000);

	// HSBフィルターを施す
	static void HSB(int type, int hue, int saturation, int bright);

	// 階調反転フィルターを施す
	static void Invert();

	// Levelフィルターを施す
	static void Level(int min, int max, int gamma, int afterMin, int afterMax);

	// グラデーションマップフィルターを施す
	static void GradiendMap(int handle);

	//描画開始
	static void DrawStart();

	//シェーダーとか適用する時用
	static void SetDrawScreenSub();

	//シェーダーとか適用したあと用
	static void SetDrawScreenMain();

	//描画終了・フリップ
	static void DrawEnd();

	//スクリーン揺れを設定
	static void SetShake(int frame, int distance);

	//残像レイヤーに現在のレイヤーをコピー
	static void SetAfterImageScreen();

	//残像レイヤーを描画
	static void DrawAfterImageScreen();

private:
	Screen();
	void init();
};


