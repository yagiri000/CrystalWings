#include "GameMgr.h"
#include <iostream>
#include <DxLib.h>
#include "Player.h"
#include "Func.h"
#include "Resource.h"
#include "Vector2.h"
#include "Collision.h"



IPlayerState::IPlayerState()
{
}

PlayerWing::PlayerWing() :
eFrame(0),
radius(400),
targetRadius(48.0),
moveRateVal(0.1),
wingNum(12),
gCenter(16, 16),
gExRate(0.5, 0.3),
gName("tilt_rect32")
{

}

void PlayerWing::update(){
	Func::moverate(radius, targetRadius, moveRateVal, 0.1);
	if (Input::keynow(KEY_INPUT_LSHIFT)){
		Func::moverate(radius, targetRadius * 0.3, moveRateVal, 0.1);
	}
	eFrame++;
}

void PlayerWing::draw(){
	for (int i = 0; i < wingNum; i++){
		double angle = 2 * PI / wingNum *i + eFrame * 0.01;
		Vector2 dpos = mgr.player_->pos + Vector2::GetPolar(radius, angle);
		int gHandle = GraphHue::handled(gName, 1.0 / wingNum * i);
		Draw::exrot3(dpos, gCenter, gExRate, angle, gHandle, 250);
	}
}


PlayerBomb::PlayerBomb() :
eFrame(0),
rate(90),
cool(0),
remainingBomb(2)
{

}

bool PlayerBomb::update(Vector2 &pos){
	eFrame++;
	if (Func::coolcount(cool) && remainingBomb > 0 && Input::keydown(KEY_INPUT_X)){
		Sound::playone("bomb_shoot");
		mgr.pBullet_.add(std::make_shared<PlayerBulletBomb>(pos));
		Screen::SetShake(30, 8);
		remainingBomb--;
		cool = rate;
		return true;
	}
	return false;
}

void PlayerBomb::draw(){
}


PlayerWeapon::PlayerWeapon() :
shotVel(0.0, -30.0),
shotCool(0),
shotRate(3)
{

}

void PlayerWeapon::update(Vector2 &pos){
	if (Func::coolcount(shotCool) && Input::keynow(KEY_INPUT_Z)){
		for (int i = -1; i <= 1; i++){
			Vector2 spos = pos + Vector2(16.0 * i, -32);
			mgr.pBullet_.add(std::make_shared<PlayerBulletNormal>(spos, shotVel, 64));
		}
		shotCool = shotRate;
	}
}

void PlayerWeapon::draw(){
}

PSAlive::PSAlive() :
pos(Player::getFirstPos()),
speed(4.0),
radius(2.0),
exRate(1.0, 1.0),
tiltAngle(0.0),
invincibleFrameMax(150),
invincibleFrame(invincibleFrameMax),
eFrame(0),
col(std::make_shared<ColCircle>(pos, radius)),
playerWing(),
IPlayerState(),
pWeapon(),
pBomb()
{
}


Vector2 PSAlive::getPos(){
	return pos;
}

int PSAlive::getBombNum(){
	return pBomb.remainingBomb;
}
void PSAlive::keyMove(){
	Vector2 shift;

	if (Input::keynow(KEY_INPUT_UP)){
		shift.y = -1.0;
	}
	if (Input::keynow(KEY_INPUT_DOWN)){
		shift.y = 1.0;
	}
	if (Input::keynow(KEY_INPUT_RIGHT)){
		shift.x = 1.0;
	}
	if (Input::keynow(KEY_INPUT_LEFT)){
		shift.x = -1.0;
	}
	shift.Normalize();
	if (Input::keynow(KEY_INPUT_LSHIFT)){
		shift *= 0.5;
	}
	pos += shift * speed;

	if (pos.x < 0 + StatusBarWidth){
		pos.x = 0 + StatusBarWidth;
	}
	if (pos.x > ScreenWidth - StatusBarWidth){
		pos.x = ScreenWidth - StatusBarWidth;
	}
	if (pos.y < 0){
		pos.y = 0;
	}
	if (pos.y > ScreenHeight){
		pos.y = ScreenHeight;
	}

}

void PSAlive::tiltUpdate(){
	double tiltMoveTo45Rate = 0.1;
	double tiltMoveToBaseRate = 0.03;
	if (Input::keynow(KEY_INPUT_RIGHT)){
		Func::moverate(tiltAngle, PI / 4, tiltMoveTo45Rate, 0.0);
	}
	if (Input::keynow(KEY_INPUT_LEFT)){
		Func::moverate(tiltAngle, -PI / 4, tiltMoveTo45Rate, 0.0);
	}
	Func::moverate(tiltAngle, 0.0, tiltMoveToBaseRate, 0.0);
	exRate.x = cos(tiltAngle);
}


bool PSAlive::isCrash(){
	//ñ≥ìGèÛë‘ÇæÇ¡ÇΩÇÁfalse
	if (invincibleFrame > 0){
		invincibleFrame--;
		return false;
	}

	auto &bulVec = mgr.eBullet_.v;
	for (auto &i = bulVec.begin(); i < bulVec.end(); i++){
		if (Col::IsCrash(col, (**i).col)){
			mgr.player_->deadRemainMinus();
			mgr.statusBar_->addStrLog("DESTROY PLAYER");
			mgr.statusBar_->addStrLog("REMAIN @" + std::to_string(mgr.player_->remainingLives));
			Screen::SetShake(30, 10);
			eff::make(pos, "PlayerDeadBomb");
			return true;
		}
	}

	return false;
}

void PSAlive::shot(){
	if (pBomb.update(pos)){
		invincibleFrame = invincibleFrameMax;
	}
	pWeapon.update(pos);
}

std::string PSAlive::getStateString(){
	std::string str;
	if (invincibleFrame > 0){
		str += "Inv @";
		str += std::to_string(invincibleFrame);
	}
	else{
		str += "Alive";
	}

	return str;
}

std::unique_ptr<IPlayerState> PSAlive::update()
{
	eFrame++;
	playerWing.update();
	tiltUpdate();
	keyMove();
	shot();
	std::static_pointer_cast<ColCircle>(col)->pos = pos;

	if (isCrash()){
		return std::make_unique<PSDead>();
	}
	return nullptr;
}

void PSAlive::draw()
{
	playerWing.draw();
	pWeapon.draw();
	pBomb.draw();
	int alpha = 250;
	if (invincibleFrame > 0){
		Draw::exrot(pos, 1.0, eFrame * 0.02, Graph::handle("invincible"), 255.0 * invincibleFrame / invincibleFrameMax);
		alpha = 64;
	}
	Draw::exrot3(pos, Vector2(32, 32), exRate, 0.0, Graph::handle("player"), alpha);
	Draw::circle(pos, radius*2.0, 0xFF8800, alpha);
}

PSDead::PSDead() :
countFrame(0),
rebirthFrame(120),
pos(mgr.player_->pos)
{
}

Vector2 PSDead::getPos(){
	return pos;
}

int PSDead::getBombNum(){
	return 0;
}

std::string PSDead::getStateString(){
	std::string str;
	str += "Dead @";
	str += std::to_string(rebirthFrame - countFrame);
	return str;
}


std::unique_ptr<IPlayerState> PSDead::update(){

	//ìGíeè¡ãé
	auto &vec = mgr.eBullet_.v;
	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto &obj = **i;
		if ((mgr.player_->pos - obj.col->getPos()).GetMagnitude() < countFrame * 8.0){
			obj.kill();
		}
	}

	countFrame++;
	if (countFrame > rebirthFrame){
		Sound::playone("mecha03");
		return std::make_unique<PSAlive>();
	}
	return nullptr;
}

void PSDead::draw(){
}

Player::Player() :
state(std::make_unique<PSAlive>()),
remainingLives(3),
eFrame(0)
{
}

Vector2 Player::getFirstPos(){
	return Vector2(ScreenWidth / 2, ScreenHeight * 0.8);
}

std::string Player::getStateString(){
	return state->getStateString();
}

int Player::getBombNum(){
	return state->getBombNum();
}

void Player::deadRemainMinus(){
	remainingLives--;
}

void Player::update(){
	eFrame++;
	std::unique_ptr<IPlayerState> ptr = state->update();
	pos = state->getPos();
	if (ptr){
		state = std::move(ptr);
	}
}

void Player::draw(){
	state->draw();
}

