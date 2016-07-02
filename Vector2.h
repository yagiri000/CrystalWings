//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------

#pragma once

//2次元上の点を表すクラス
class Vector2
{
public:
	double x;
	double y;

	static const Vector2 zero;

	//コンストラクタ定義
	Vector2();
	Vector2(double x_, double y_);

	//オペレーターオーバーロード
	Vector2& operator +=(const Vector2& t);
	Vector2& operator -=(const Vector2& t);
	Vector2 operator +(const Vector2& t);
	Vector2 operator -(const Vector2& t);
	Vector2 operator *(double t);
	Vector2 operator /(double t);
	Vector2& operator *=(double t);
	Vector2& operator /=(double t);

	//内積
	double operator *(const Vector2& t);

	//外積
	double cross(const Vector2& t);

	//操作関数
	void Set(double x_, double y_);

	//原点を中心に回転
	void Rotate(double rad);

	//centerを中心に回転
	void RotateOnPoint(double rad, const Vector2 &center);

	//原点を中心にベクトルを回転したものを返す
	Vector2 GetRotate(double rad);

	//centerを中心に回転したベクトルを返す
	Vector2 GetRotateOnPoint(double rad, const Vector2 &center);

	//dx,dy分だけ移動
	void Translate(double dx, double dy);

	//ベクトルの大きさを返す
	double GetMagnitude();

	//ベクトルの大きさを返す
	double GetSqrMagnitude();

	//ベクトルを正規化する
	void Normalize();

	//正規化されたベクトルを返す
	Vector2 GetNormalized();

	//ベクトルの角度を返す
	double GetAngle();

	//極座標系式で表されたベクトルを返す static
	static Vector2 GetPolar(double r, double angle);

	//指定した範囲内にベクトルを修正
	void maximize(double xMin, double xMax, double yMin, double yMax);
};