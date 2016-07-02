#include "PlayerBullet.h"
#include "GameMgr.h"

IPlayerBullet::IPlayerBullet(Vector2 pos_, const std::string& gHName, double damage_) :
pos(pos_),
gHandleName(gHName),
eFrame(0),
alpha(128),
damage(damage_)
{
}

void IPlayerBullet::update(){
	eFrame++;
	move();
	isCrash();
	isScreenOut();
}

PlayerBulletNormal::PlayerBulletNormal(Vector2& pos_, Vector2& vel_, double length_) :
vel(vel_),
length(length_),
graphicSize(64, 64),
IPlayerBullet(pos_, "playerBullet", 5.0)
{
	col = std::make_shared<ColLine>(pos - Vector2::GetPolar(length * 0.5, vel.GetAngle()), pos + Vector2::GetPolar(length * 0.5, vel.GetAngle()));
}

void PlayerBulletNormal::isCrash(){
	auto &vec = mgr.enemy_.v;
	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto &obj = **i;
		if (obj.IsDead == false && Col::IsCrash(col, obj.col)){
			obj.hp -= damage;
			if (obj.hp < 0.0){
				obj.IsDead = true;
			}
			eff::make(pos, "CirBlank");
			IsDead = true;
		}
	}
}

void PlayerBulletNormal::isScreenOut(){
	if (!Func::IsAlivePos(pos)){
		IsDead = true;
	}
}

void PlayerBulletNormal::move(){
	pos += vel;

	//当たり判定位置更新
	auto ptr = std::static_pointer_cast<ColLine>(col);
	ptr->start = pos - Vector2::GetPolar(length * 0.5, vel.GetAngle());
	ptr->end = pos + Vector2::GetPolar(length * 0.5, vel.GetAngle());
}

void PlayerBulletNormal::draw(){
	Draw::exrot3(pos, Vector2(32, 32), Vector2(length / graphicSize.x, 1.0), vel.GetAngle(), Graph::handle(gHandleName), alpha, 0);
	//Col::draw(col, 0xFF0000);
}


PlayerBulletBomb::PlayerBulletBomb(Vector2& pos_) :
vel(Vector2(0, -4)),
radius(180.0),
IPlayerBullet(pos_, "playerBullet", 100.0)
{
	col = std::make_shared<ColCircle>(pos_, radius);
}

void PlayerBulletBomb::isCrash(){
	auto &vec = mgr.eBullet_.v;
	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto &obj = **i;
		if (obj.IsDead == false && Col::IsCrash(col, obj.col)){
			obj.kill();
			obj.IsDead = true;
		}
	}


	auto &enemy = mgr.enemy_.v;
	for (auto &i = enemy.begin(); i < enemy.end(); i++){
		auto &obj = **i;
		if (obj.IsDead == false && Col::IsCrash(col, obj.col)){
			obj.hp -= damage;
			if (obj.hp < 0.0){
				obj.IsDead = true;
			}
			eff::make(pos, "CirBlank");
		}
	}
}

void PlayerBulletBomb::isScreenOut(){
	if (pos.y < -radius){
		IsDead = true;
	}
}

void PlayerBulletBomb::move(){
	pos += vel;

	//当たり判定位置更新
	auto ptr = std::static_pointer_cast<ColCircle>(col);
	ptr->pos = pos;

	for (int i = 0; i < 8; i++){
		eff::make(Random::RandInCircle(radius) + pos, "BombSplash");
	}
}

void PlayerBulletBomb::draw(){
	//Col::draw(col, 0xFF0000);
}

