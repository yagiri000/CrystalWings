#pragma once
#include <iostream>
#include "Vector2.h"

#define DEBUG 1

const double PI(4 * atan(1));
const double DegToRad(PI / 180.0);
const double RadToDeg(180.0f / PI);
const double SQRT2(sqrt(2.0));

//スクリーンサイズ
const int ScreenWidth(800);
const int ScreenHeight(600);

//ステータスバーの幅
const int StatusBarWidth(150);

//スクリーンからどれだけ離れて生存できるか
const double AliveLength(100);


using lint = long long int;