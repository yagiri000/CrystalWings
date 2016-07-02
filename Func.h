#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "myglobal.h"
#include "Resource.h"
#include "Vector2.h"

//  2014/12/07 更新

/*
class Draw
class Input
class Random

namespace Func
	-当たり判定
	-ベクトル
	-イージング曲線
	-便利関数

*/




//シングルトンDrawクラス
class Draw
{
private:
	Draw();

public:
	Draw(const Draw& r) = delete;
	Draw& operator=(const Draw& r) = delete;

	double dx;
	double dy;
	Vector2 shift_vec;

	static Draw& get();

	static void setdxdy(int x, int y);

	static void normal(int x, int y, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void center(int x, int y, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	static void lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	static void box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centerbox(double centerx, double centery, double width, double height, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circle(int x, int y, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centertext_space(int x, int y, int color, int fonthandle, int space, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void normal(const Vector2& pos, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void center(const Vector2& pos, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	static void lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	static void box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void circle(const Vector2& pos, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void text(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centertext(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void righttext(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);

	static void centertext_space(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA);
};

using Draw_ = Draw;

//マウス座標・キー状態・起動からのフレーム数

//!!!!!!!!!!!!! 注意 !!!!!!!!!!!!!
//getする前にstaticメンバにアクセスするのは不可能

class Input{
public:

	Input();

	Input& operator=(const Input& a) = delete;
	Input(const Input& a) = delete;

	static Input& get();

	static void update();

	static bool keynow(int i);

	static bool keydown(int i);

	static bool keyup(int i);

	static int keyframe(int i);

	static int mousex();

	static int mousey();

	static Vector2 mousePos();

	static int eframe();

	static void setAllzeroframe(int t);

	static void Allzeroon();

	static void Allzerooff();

private:
	int m_mousex = 0;
	int m_mousey = 0;//マウス座標
	int m_eframe = 0;//経過フレーム
	Vector2 m_mousePos;

	char buf[256];
	int keystate[256];
	int keystate_pre[256];

	//setAllzeroframe関数でロックされるフレーム数 waitframe>0で全配列内容0に　
	int Allzeroframe;

	//IsAll0 == trueで全配列内容0に
	bool IsAllzero;
	
	void do_update();

	void Allzero();
};


//シングルトンRandomクラス
class Random
{
	std::mt19937 mt;
	Random();

public:
	Random(const Random& r) = delete;
	Random& operator=(const Random& r) = delete;

	static Random& get();

	static void SeedSetUseRD();

	static void Initialize(int seed);

	static std::mt19937& getMT();

	static unsigned int RamdomDeviceValue();

	static int Rand();

	static int Rand(int max);

	static int Rand(int min, int max);

	static int RandPM1();

	static double Value();

	static double FRand(double max);

	static double FRand(double min, double max);

	static double FRandND(double mean, double sigma);

	static double FRandND(double mean, double sigma, double limit);

	static double NormalDist(double ave, double range);

	static double FRadRand();

	static double FRadRand(double deg_min, double deg_max);

	static double FRadRandND(double deg_mean, double deg_sigma = 0);

	static void RandOnCircle(double r, double &x, double &y);

	static void RandOnCircle(double r, double &x, double &y, double &ang);

	static void RandInCircle(double r, double &x, double &y);

	static void RandInCircle(double r, double &x, double &y, double &ang);

	static Vector2 RandOnCircle(double r);

	static Vector2 RandInCircle(double r);

	static Vector2 RandScreenEdge();

	static bool RandBool(double p);
};

namespace Func{

	double Sqr(double x);

	double Dot2D(double Ax, double Ay, double Bx, double By);

	double Cross2D(double Ax, double Ay, double Bx, double By);

	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2);

	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2);

	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y);

	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad);

	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad);

	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height);

	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size);

	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y);

	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2);

	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y);

	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y);

	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey);

	void rotateonzero(double &x, double &y, double ang);

	void rotateonpoint(double &x, double &y, double centerx, double centery, double ang);

	void normalizedVector(double &vx, double &vy, double sx, double sy);

	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey);

	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	void addVector(double r, double angle, double &resultx, double &resulty);

	void polartoxy(double &x, double &y, double r, double ang);

	double calAngle(double x, double y);

	double calAngle(double sx, double sy, double ex, double ey);

	double linef(double startx, double dif, double time_now, double time_end);

	double quadraticf(double startx, double dif, double time_now, double time_end);

	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end);

	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end);

	double ease_cubic_in(double t, double b, double c, double d);

	double ease_cubic_out(double t, double b, double c, double d);

	double ease_cubic_inout(double t, double b, double c, double d);

	double ease_sin_in(double t, double b, double c, double d);

	double ease_sin_out(double t, double b, double c, double d);

	double ease_sin_inout(double t, double b, double c, double d);

	double ease_exp_in(double t, double b, double c, double d);

	double ease_exp_out(double t, double b, double c, double d);

	double ease_exp_inout(double t, double b, double c, double d);

	double ease_sqrt_in(double t, double b, double c, double d);

	double ease_sqrt_out(double t, double b, double c, double d);

	double ease_sqrt_inout(double t, double b, double c, double d);

	double bz_curve(double p1, double p2, double p3, double t);

	double bz_curve(double p1, double p2, double p3, double nowt, double endt);

	int Repeat(int frame, int loop_num);

	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint);

	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t);

	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1, const Vector2& ControlPoint2, const Vector2& End, float t);

	DWORD GetColorHSV(int h, int s, int v);

	int HSVtoRGB(int h, int s, int v);

	void SetDrawBrightHSV(int h, int s, int v);

	void SetDrawBrightInt(int col);

	int abs_angle(double angle1, double angle2);

	void moverate(double &x, double tarx, double rate, double erange = 1.0);

	void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist = 0.5);

	void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist = 0.5);

	double dist(double x, double y);

	double dist(double x1, double y1, double x2, double y2);

	double distSqr(double x1, double y1, double x2, double y2);

	bool coolcount(int &cool);

	double sinsec(double base, double a, double t, double frame);

	Vector2 GetScreenCenter();

	bool IsAlivePos(const Vector2 &pos);


	std::string randStr();

	std::string randStr(int loop);

	Vector2 ease_v2_sin(int eFrame, int reqFrame, Vector2 start, Vector2 end);

	std::string randStrVec(std::vector<std::string> strVec);
}
