#include "EnemyBullet.h"
#include "GameMgr.h"

IEnemyBullet::IEnemyBullet(std::shared_ptr<ICollision> col_, double hue_, const std::string& gHName) :
col(col_),
hue(hue_),
gHandleName(gHName),
eFrame(0)
{
	Sound::playone("enemy_shot");
}

void IEnemyBullet::update(){
	eFrame++;
	move();
	isScreenOut();
}

EBStraightLine::EBStraightLine(Vector2& pos_, Vector2& vel_, double length_, double hue_):
pos(pos_),
vel(vel_),
length(length_),
graphicSize(32, 32),
IEnemyBullet(std::make_shared<ColLine>(pos_ - Vector2::GetPolar(length_ * 0.5, vel_.GetAngle()), pos_ + Vector2::GetPolar(length_ * 0.5, vel_.GetAngle())),
hue_, "tilt_rect32")
{
}

void EBStraightLine::isScreenOut(){
	if (!Func::IsAlivePos(pos)){
		IsDead = true;
	}
}

void EBStraightLine::move(){
	pos += vel;

	//当たり判定位置更新
	auto ptr = std::static_pointer_cast<ColLine>(col);
	ptr->start = pos - Vector2::GetPolar(length * 0.5, vel.GetAngle());
	ptr->end = pos + Vector2::GetPolar(length * 0.5, vel.GetAngle());
}

void EBStraightLine::kill(){
	auto &p = eff::make(pos, "Trail");
	p->center = Vector2(16, 16);
	p->exRate = Vector2(length / graphicSize.x, 0.2);
	p->angle = vel.GetAngle();
	p->ghandle = GraphBullet::handled(gHandleName, hue);
	
	int score = mgr.scoreMgr_->addScoreBulletKill();
	std::string str = "+" + std::to_string(score);
	mgr.effect_.add(std::make_shared<StrEf>(pos, str));

	IsDead = true;
}

void EBStraightLine::draw(){
	Draw::exrot3(pos, Vector2(16, 16), Vector2(length / graphicSize.x, 0.2), vel.GetAngle(), GraphBullet::handled(gHandleName, hue), 255);
	//Col::draw(col, 0xFF0000);
}



EBStraightLineSpeedEaseCos::EBStraightLineSpeedEaseCos
(Vector2& pos_, Vector2& vel_, double length_, double hue_) :
EBStraightLine(pos_, vel_, length_, hue_),
easeAllFrame(60)
{
}

double EBStraightLineSpeedEaseCos::easeCos(int frame, int allFrame){
	if (frame < allFrame){
		return cos(2 * PI * frame / allFrame) * 0.5 + 0.5;
	}
	return 1.0;
}

void EBStraightLineSpeedEaseCos::move(){
	pos += vel * easeCos(eFrame, 60);

	//当たり判定位置更新
	auto ptr = std::static_pointer_cast<ColLine>(col);
	ptr->start = pos - Vector2::GetPolar(length * 0.5, vel.GetAngle());
	ptr->end = pos + Vector2::GetPolar(length * 0.5, vel.GetAngle());
}
