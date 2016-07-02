//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------
#pragma once
#include <iostream>
#include "Vector2.h"

const Vector2 Vector2::zero(0, 0);

//2������̓_��\���N���X
//�R���X�g���N�^��`
Vector2::Vector2() :
x(0), y(0)
{
}


Vector2::Vector2(double x_, double y_) : 
x(x_), y(y_)
{
}

//�I�y���[�^�[�I�[�o�[���[�h
Vector2& Vector2::operator +=(const Vector2& t)
{
	x += t.x;
	y += t.y;
	return *this;
}
Vector2& Vector2::operator -=(const Vector2& t)
{
	x -= t.x;
	y -= t.y;
	return *this;
}
Vector2 Vector2::operator +(const Vector2& t){
	Vector2 temp;
	temp.x = x + t.x;
	temp.y = y + t.y;
	return temp;
}
Vector2 Vector2::operator -(const Vector2& t){
	Vector2 temp;
	temp.x = x - t.x;
	temp.y = y - t.y;
	return temp;
}
Vector2 Vector2::operator *(double t){
	Vector2 temp;
	temp.x = x * t;
	temp.y = y * t;
	return temp;
}
Vector2 Vector2::operator /(double t){
	Vector2 temp;
	temp.x = x / t;
	temp.y = y / t;
	return temp;
}
Vector2& Vector2::operator *=(double t)
{
	x *= t;
	y *= t;
	return *this;
}
Vector2& Vector2::operator /=(double t)
{
	x /= t;
	y /= t;
	return *this;
}

//����
double Vector2::operator *(const Vector2& t){
	return x * t.x + y * t.y;
}

//�O��
double Vector2::cross(const Vector2& t){
	return x * t.y - y * t.x;
}

//����֐�
void Vector2::Set(double x_, double y_)
{
	x = x_;
	y = y_;
}

//���_�𒆐S�ɉ�]
void Vector2::Rotate(double rad)
{
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = x;	//�ꎞ�i�[
	x = cost * tx - sint * y;		// ( cos�� -sin��) ( x )
	y = sint * tx + cost * y;		// ( sin�� xos�� ) ( y )
}

//center�𒆐S�ɉ�]
void Vector2::RotateOnPoint(double rad, const Vector2 &center)
{
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = x - center.x;	//�ꎞ�i�[
	double ty = y - center.y;	//�ꎞ�i�[
	x = cost * tx - sint * ty + center.x;		// ( cos�� -sin��) ( x )
	y = sint * tx + cost * ty + center.y;		// ( sin�� xos�� ) ( y )
}

//���_�𒆐S�Ƀx�N�g������]�������̂�Ԃ�
Vector2 Vector2::GetRotate(double rad){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = temp.x;	//�ꎞ�i�[
	temp.x = cost * tx - sint * temp.y;		// ( cos�� -sin��) ( x )
	temp.y = sint * tx + cost * temp.y;		// ( sin�� xos�� ) ( y )
	return temp;
}

//center�𒆐S�ɉ�]�����x�N�g����Ԃ�
Vector2 Vector2::GetRotateOnPoint(double rad, const Vector2 &center){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
	double tx = temp.x - center.x;	//�ꎞ�i�[
	double ty = temp.y - center.y;	//�ꎞ�i�[
	temp.x = cost * tx - sint * ty + center.x;		// ( cos�� -sin��) ( x )
	temp.y = sint * tx + cost * ty + center.y;		// ( sin�� xos�� ) ( y )
	return temp;
}

//dx,dy�������ړ�
void Vector2::Translate(double dx, double dy)
{
	x += dx;
	y += dy;
}

//�x�N�g���̑傫����Ԃ�
double Vector2::GetMagnitude(){
	return sqrt(x*x + y*y);
}

//�x�N�g���̑傫����Ԃ�
double Vector2::GetSqrMagnitude(){
	return x*x + y*y;
}

//�x�N�g���𐳋K������
void Vector2::Normalize(){
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	x /= r;
	y /= r;
}

//���K�����ꂽ�x�N�g����Ԃ�
Vector2 Vector2::GetNormalized(){
	Vector2 temp = *this;
	double r = sqrt(x*x + y*y);
	if (r < 0.001){
		r = 0.001;
	}
	temp.x /= r;
	temp.y /= r;
	return temp;
}

//�x�N�g���̊p�x��Ԃ�
double Vector2::GetAngle(){
	return atan2(y, x);
}

//�ɍ��W�n���ŕ\���ꂽ�x�N�g����Ԃ� static
Vector2 Vector2::GetPolar(double r, double angle){
	Vector2 temp;
	temp.x = r * cos(angle);
	temp.y = r * sin(angle);
	return temp;
}

//�w�肵���͈͓��Ƀx�N�g�����C��
void Vector2::maximize(double xMin, double xMax, double yMin, double yMax)
{
	if (x < xMin){ x = xMin; }
	if (x > xMax){ x = xMax; }
	if (y < yMin){ y = yMin; }
	if (y > yMax){ y = yMax; }
}


