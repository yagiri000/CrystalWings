//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------

//-------------------------------------------
//
//                n. i. a.
//
//                         Effect Draw System
//-------------------------------------------

#include "GameMgr.h"
#include "Resource.h"
#include "Func.h"

IEffect::IEffect() :
PI(3.141592653589793),
elapsedtime(0)
{
}



//const Vector2 &pos,
//const Vector2 &velocity,
//const Vector2 &acceleration,
//double sppedrate,
//const Vector2 &center,
//const Vector2 &exRate,
//const Vector2 &exRatePlus,
//double angle,
//double angleplus,
//double alpha,
//double alphaplus,
//int turnflag,
//int blendmode,
//int ghandle,
//int deleteframe



void IEffect::set(
	const Vector2 &pos,
	const Vector2 &center,
	const Vector2 &exRate,
	double angle,
	double alpha,
	const Vector2 &velocity,
	const Vector2 &acceleration,
	const Vector2 &exRatePlus,
	double sppedrate,
	double angleplus,
	double alphaplus,
	int turnflag,
	int blendmode,
	int ghandle,
	int deleteframe
	)
{
	this->pos = pos;
	this->center = center;
	this->exRate = exRate;
	this->angle = angle;
	this->alpha = alpha;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->exRatePlus = exRatePlus;
	this->sppedrate = sppedrate;
	this->angleplus = angleplus;
	this->alphaplus = alphaplus;
	this->turnflag = turnflag;
	this->blendmode = blendmode;
	this->ghandle = ghandle;
	this->deleteframe = deleteframe;
}

void IEffect::move(){
	pos += velocity;
	velocity += acceleration;

	velocity *= sppedrate;

	exRate += exRatePlus;

	angle += angleplus;
	alpha += alphaplus;
}

void IEffect::update(){
	if (elapsedtime > -1){
		move();
	}

	elapsedtime++;

	if (elapsedtime > deleteframe){
		IsDead = true;
	}
}

void IEffect::draw(){
	if (elapsedtime > -1){
		Draw::exrot3(pos, center, exRate, angle, ghandle, alpha, turnflag, blendmode);
	}
}

void IEffect::wait(int f){
	elapsedtime = -f;
}


//エフェクトを生成するクラスの基底クラス
ISet::ISet(){
};

void ISet::move(){
}

void ISet::update(){
	if (elapsedtime > -1){
		move();
	}

	elapsedtime++;

	if (elapsedtime > deleteframe){
		IsDead = true;
	}
}

void ISet::draw(){
}

PlayerDeadBomb::PlayerDeadBomb(const Vector2 &pos)
{
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, -16, 0, DX_BLENDMODE_ALPHA, -1, 90);
}

void PlayerDeadBomb::move(){
	for (int i = 0; i < 5; i++){
		Vector2 epos = pos + Random::RandOnCircle(elapsedtime * 8.0);
		eff::make(epos, "BoxBlank");
	}
	Sound::playone("mybomb02");
}

EnemyDeadBomb::EnemyDeadBomb(const Vector2 &pos)
{
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		255, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, -16, 0, DX_BLENDMODE_ALPHA, -1, 15);
	eff::make(pos, "Debri", 15);
}

void EnemyDeadBomb::move(){
	for (int i = 0; i < 5; i++){
		Vector2 epos = pos + Random::RandOnCircle(elapsedtime * 8);
		eff::make(epos, "CirBlank");
	}
	Sound::playone("mybomb01");
}


//個々のエフェクトの設定ファイル
PlayerTrail::PlayerTrail(const Vector2 &pos){
	set(pos, Vector2(32, 32), Vector2(1.0, 1.0), 0.0,
		50, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.1, 0.1), 1.0,
		0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 5);
};



Debri::Debri(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), Random::FRadRand(),
		200, Random::RandInCircle(20.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 0.9,
		Random::FRand(0.1, 0.4)*Random::RandPM1(), -8, 0, DX_BLENDMODE_ALPHA, GraphHue::handled("rect32", Random::FRand(1.0)), 25);
};

Trail::Trail(const Vector2 &pos){
	set(pos, Vector2(32, 32), Vector2(1.0, 1.0), 0.0,
		100, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.1, 0.1), 1.0,
		0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 10);
};

TitleEf::TitleEf(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), 0.0,
		64, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, GraphHue::handled("gra32", Random::FRand(1.0)), 999);
	exRate = Vector2(Random::FRand(2.5, 4.5), Random::FRand(0.5, 1.5));
	double rate = Random::FRand(0.3, 2.0);
	exRate *= rate;
	velocity = Vector2(6.0 * rate, 0.0);
};

void TitleEf::update(){
	if (elapsedtime > -1){
		move();
	}

	elapsedtime++;

	if (elapsedtime > deleteframe || pos.x > ScreenWidth + 50){
		IsDead = true;
	}
}

StrEf::StrEf(const Vector2 &pos, const std::string &str_):
str(str_)
{
	set(pos, Vector2(0, 0), Vector2(1.0, 1.0), 0.0,
		255, Vector2(0.0, -1.0), Vector2(0.0, 0.0), Vector2(0.0, 0.0), 1.0,
		0.0, -255.0/60, 0, DX_BLENDMODE_ALPHA, font("OS18") , 60);
}

void StrEf::draw(){
	Draw::centertext(pos, 0xFF8888, ghandle, str, alpha);
}


fire::fire(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(4.0, 4.0), 0.0,
		200, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(-0.15, -0.15), 1.0,
		0.0, -8, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 25);
	velocity.x = Random::FRand(-1, 1);
	velocity.y = Random::FRand(-15, -5);
};


slash::slash(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(0.5, 1.0), 0.0,
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(-0.05, 2.6), 1.0,
		0.0, -25, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 10);
	angle = Random::FRadRand();

};


bomb::bomb(const Vector2 &pos){
	set(pos, Vector2(16, 16), Vector2(1.0, 1.0), Random::FRadRand(),
		255.0, Vector2(0.0, 0.0), Vector2(0.0, 0.0), Vector2(0.3, 0.3), 1.0,
		0.01, -25, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 5);
};


CirBlank::CirBlank(const Vector2 &pos){
	set(pos, Vector2(32, 32), Vector2(0.0, 0.0), Random::FRadRand(),
		200, Random::RandOnCircle(0.7), Random::RandOnCircle(0.1), Vector2(0.0, 0.0), 1.0,
		0.0, -1.0, 0, DX_BLENDMODE_ALPHA, 0, 16);

	col = Random::Rand(360);
	angle = Random::FRadRand();
	angleplus = Random::FRand(0.01, 0.02) * Random::RandPM1();
	exRatePlus.x = exRatePlus.y = Random::FRand(1.0 / 16.0 * 0.5, 1.0 / 16.0);
};

void CirBlank::draw(){
	Func::SetDrawBrightHSV(col, 128, 255);
	Draw::exrot3(pos, center, exRate, angle,
		GraphDiv::handle("cir_blank", elapsedtime), alpha, turnflag, blendmode);
	Func::SetDrawBrightInt(0xFFFFFF);
}


BoxBlank::BoxBlank(const Vector2 &pos){
	set(pos, Vector2(32, 32), Vector2(0.3, 0.3), Random::FRadRand(),
		200, Random::RandOnCircle(0.7), Random::RandOnCircle(0.1), Vector2(0.0, 0.0), 1.0,
		0.0, -1.0, 0, DX_BLENDMODE_ALPHA, 0, 16);

	col = Random::Rand(360);
	angle = Random::FRadRand();
	angleplus = Random::FRand(0.01, 0.02) * Random::RandPM1();
	exRatePlus.x = exRatePlus.y = Random::FRand(1.0 / 16.0 * 0.5, 1.0 / 16.0);
};

void BoxBlank::draw(){
	Func::SetDrawBrightHSV(col, 128, 255);
	Draw::exrot3(pos, center, exRate, angle,
		GraphDiv::handle("box_blank", elapsedtime), alpha, turnflag, blendmode);
	Func::SetDrawBrightInt(0xFFFFFF);
}


BombSplash::BombSplash(const Vector2 &pos){
	set(pos, Vector2(32, 32), Vector2(0.3, 0.3), 0.0,
		200, Random::RandOnCircle(0.0), Random::RandOnCircle(0.0), Vector2(0.0, 0.0), 1.0,
		0.0, 0.0, 0, DX_BLENDMODE_ALPHA, 0, 16);

	col = Random::Rand(360);
	angle = PI / 4;
	exRatePlus.x = exRatePlus.y = Random::FRand(1.0 / 16.0 * 0.5, 1.0 / 16.0);
};

void BombSplash::draw(){
	Func::SetDrawBrightHSV(col, 128, 255);
	Draw::exrot3(pos, center, exRate, angle,
		GraphDiv::handle("box_blank", elapsedtime), alpha, turnflag, blendmode);
	Func::SetDrawBrightInt(0xFFFFFF);
}



BombRetro::BombRetro(const Vector2 &pos){
	set(pos, Vector2(128, 128), Vector2::zero, Random::FRadRand(),
		255.0, Vector2::zero, Vector2::zero, Vector2::zero, 1.0,
		0.0, 0.0, 0, DX_BLENDMODE_ALPHA, Graph::handle("bomb_retro"), 10);
};
void BombRetro::move(){
	pos += velocity;
	velocity += acceleration;

	velocity *= sppedrate;

	auto func = [&](){
		return 0.5 * sin((double)PI * elapsedtime / deleteframe);
	};
	exRate.x = exRate.y = func();

	angle += angleplus;
	alpha += alphaplus;
}