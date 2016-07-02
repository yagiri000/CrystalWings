#include "GameMgr.h"
#include "Func.h"
#include "Resource.h"

HueKeeper::HueKeeper() :
mode_((mode)(Random::Rand(0, 1))),
hue(Random::FRand(1.0)),
dHue(0.0),
rainbowDif(1.0)
{
	if (Random::RandBool(0.1)){
		rainbowDif = Random::FRand(0.1, 1.0);
	}
	if (Random::RandBool(0.33)){
		dHue = Random::FRand(0.1);
	}
}


double HueKeeper::getHue(int num, int allnum){
	if (mode_ == constant){
		return hue;
	}
	else if (mode_ == rainbow){
		if (allnum == 0){
			return hue;
		}
		else{
			return rainbowDif * num / allnum + hue;
		}
	}
	else{
		return 0.0;
	}
}

void HueKeeper::rotHue(){
	hue += dHue;
}

IMover::IMover(Vector2 &pos) : 
firstPos(pos),
eFrame(0)
{
}

void IMover::update(Vector2 &pos){
	eFrame++;
	move(pos);
}

MoverToPlayer::MoverToPlayer(Vector2 &pos) :
IMover(pos),
speed(Random::FRand(1.0, 2.0)),
vel((mgr.player_->pos - pos).GetNormalized() * speed)
{
}

void MoverToPlayer::move(Vector2 &pos){
	pos += vel;
}

MoverToCenter::MoverToCenter(Vector2 &pos) :
IMover(pos),
speed(Random::FRand(1.0, 2.0)),
vel((Func::GetScreenCenter() - pos).GetNormalized() * speed)
{
}

void MoverToCenter::move(Vector2 &pos){
	pos += vel;
}


Mover3Pos::Mover3Pos(Vector2 &pos) :
IMover(pos),
moveRatePal(0.04),
targetPos(pos),
moveCount(0),
moveCountMax(4)
{
}

void Mover3Pos::move(Vector2 &pos){
	if (eFrame % 180 == 1){
		if (moveCount < moveCountMax){
			moveCount++;
			targetPos = Func::GetScreenCenter() + Vector2(Random::Rand(-200, 200), -Random::Rand(0, 250));
		}
		else{
			targetPos = Func::GetScreenCenter() + Vector2(0, -ScreenHeight);
		}
	}

	Func::moverate(pos, targetPos, moveRatePal);
}


Mover1Pos::Mover1Pos(Vector2 &pos) :
IMover(pos),
moveRatePal(0.04),
targetPos(Func::GetScreenCenter() + Vector2(Random::Rand(-200, 200), -Random::Rand(0, 250)))
{
}

void Mover1Pos::move(Vector2 &pos){
	if (eFrame == 420){
		targetPos = Func::GetScreenCenter() + Vector2(0, -ScreenHeight);
	}
	Func::moverate(pos, targetPos, moveRatePal);
}

IWeapon::IWeapon() :
eFrame(0),
hueKeeper()
{
}

void IWeapon::update(Vector2 &pos){
	eFrame++;
	shot(pos);
}

WeaponToPlayer::WeaponToPlayer(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(3.0, 6.0)),
rate(40),
cool(0)
{
}

void WeaponToPlayer::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		double length = 64.0;
		auto vel = (mgr.player_->pos - pos).GetNormalized() * speed;
		mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(0, 0)));
	}
}


WeaponToPlayerSomeNum::WeaponToPlayerSomeNum(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(3.0, 6.0)),
num(Random::Rand(3, 6)),
rate(40),
cool(0)
{
}

void WeaponToPlayerSomeNum::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		double length = 64.0;
		for (int i = 1; i < num + 1; i++){
			double rate = (double)i / (num + 1);
			auto vel = (mgr.player_->pos - pos).GetNormalized() * speed * rate;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(0, 0)));

		}
	}
}


WeaponToPlayerParallel::WeaponToPlayerParallel(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(5.0, 6.0)),
distOnBullet(Random::FRand(8.0, 60.0)),
num(Random::Rand(1, 3) * 2 + 1),
rate(Random::Rand(45, 60)),
cool(0)
{
}

void WeaponToPlayerParallel::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		double length = 64.0;
		for (int i = -num / 2; i <= num / 2; i++){
			Vector2 vel = (mgr.player_->pos - pos).GetNormalized() * speed;
			Vector2 spos = pos + vel.GetNormalized() * length * 0.5 + vel.GetNormalized().GetRotate(PI / 2) * distOnBullet * i;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(spos, vel, length, hueKeeper.getHue(0, 0)));
		}
	}
}

WeaponToPlayerNWay::WeaponToPlayerNWay(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(3.0, 7.0)),
angleDif(Random::FRand(PI / 40, PI / 9)),
num(Random::Rand(1, 3) * 2 + 1),
rate(Random::Rand(45, 60)),
cool(0)
{
}

void WeaponToPlayerNWay::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		double length = 64.0;
		for (int i = -num / 2; i <= num / 2; i++){
			Vector2 vel = (mgr.player_->pos - pos).GetNormalized().GetRotate(angleDif * i) * speed;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(0, 0)));
		}
	}
}



WeaponSpreadSinAngle::WeaponSpreadSinAngle(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(3.0, 7.0)),
firstAngle((mgr.player_->pos - pos).GetAngle()),
angleDif(Random::FRand(PI / 18, PI / 9)),
shotAngle(0.0),
shotAnglePlus(Random::FRand(PI / 12, PI / 6)),
rate(Random::Rand(40, 60)),
cool(0)
{
}

void WeaponSpreadSinAngle::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		double length = 64.0;
		Vector2 vel = Vector2::GetPolar(speed, firstAngle + angleDif * sin(shotAngle));
		shotAngle += shotAnglePlus;
		mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(0, 0)));
	}
}

WeaponAround::WeaponAround(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(2.0, 6.0+ 1.0)),
num(Random::Rand(4, 15)),
baseAngle(Random::FRadRand()),
rate(60),
cool(0)
{
}

void WeaponAround::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		for (int i = 0; i < num; i++){
			Vector2 vel = Vector2::GetPolar(speed, 2 * PI / num * i + baseAngle);
			double length = 64.0;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, 64.0, hueKeeper.getHue(i, num)));
		}
	}
}

WeaponAroundSomeNum::WeaponAroundSomeNum(Vector2 &pos) :
WeaponAround(pos),
numOnLine(Random::Rand(2, 5)),
dAngle(Random::FRadRand())
{
	num = Random::Rand(4, 8);
	rate = Random::Rand(50, 70);
}

void WeaponAroundSomeNum::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		baseAngle += dAngle;
		for (int i = 0; i < num; i++){
			for (int j = 1; j < numOnLine + 1; j++){
				double speedRate = (double)j / (numOnLine + 1) * 0.5 + 0.5;
				Vector2 vel = Vector2::GetPolar(speed * speedRate, 2 * PI / num * i + baseAngle);
				double length = 64.0;
				mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, 64.0, hueKeeper.getHue(i, num)));
			}
		}
	}
}



WeaponAroundToPlayer::WeaponAroundToPlayer(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(2.0, 6.0 + 1.0)),
num(Random::Rand(4, 10 + 1.0 * 2.0)),
rate(30),
cool(0)
{
}

void WeaponAroundToPlayer::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		for (int i = 0; i < num; i++){
			double baseAngle = (mgr.player_->pos - pos).GetAngle();
			Vector2 vel = Vector2::GetPolar(speed, 2 * PI / num * i + baseAngle);
			double length = 64.0;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(i, num)));
		}
	}
}


WeaponAroundSinAngle::WeaponAroundSinAngle(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(2.0, 6.0 + 1.0)),
num(Random::Rand(4, 12)),
firstAngle((mgr.player_->pos - pos).GetAngle()),
angleDif(Random::FRand(PI / 8, PI / 2)),
shotAngle(0.0),
shotAnglePlus(Random::FRand(PI / 12, PI / 6)),
rate(60),
cool(0)
{
}

void WeaponAroundSinAngle::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		cool = rate;
		for (int i = 0; i < num; i++){
			Vector2 vel = Vector2::GetPolar(speed, 2 * PI / num * i + firstAngle + angleDif * sin(shotAngle));
			double length = 64.0;
			mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(i, num)));
		}
		shotAngle += shotAnglePlus;
	}
}

WeaponAnglePlus::WeaponAnglePlus(Vector2 &pos) :
IWeapon(),
speed(Random::FRand(2.0, 9.0)),
nowAngle(Random::FRadRand()),
dAngle(Random::FRand(0.2, 0.4) * Random::RandPM1()),
cool(0),
rate(3)
{
}

void WeaponAnglePlus::shot(Vector2 &pos){
	if (Func::coolcount(cool)){
		nowAngle += dAngle;
		cool = rate;
		Vector2 vel = Vector2::GetPolar(speed, nowAngle);
		double length = 64.0;
		mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos + vel.GetNormalized() * length * 0.5, vel, length, hueKeeper.getHue(0, 0)));
		hueKeeper.rotHue();
		//mgr.eBullet_.add(std::make_shared<EBStraightLineSpeedEaseCos>(pos, Vector2(1.0, 0.0), 64.0, 1.0));
	}
}


IGraphic::IGraphic() :
eFrame(0),
hueKeeper(),
alpha(230)
{
}

void IGraphic::update(){
	eFrame++;
}


GraphicCore::GraphicCore() :
rotAngle(0.0),
coreHue(Random::FRand(1.0)),
gHandleName(Func::randStrVec({ "circle32", "lack_rect32" }))
{
	if (Random::Rand(100) < 30){
		rotAngle = PI / 4;
	}
}

void GraphicCore::draw(Vector2 &pos){
	Draw::exrot(pos, 0.4, rotAngle, GraphHue::handled(gHandleName, coreHue), alpha);
}

double GraphicCore::getRadius(){
	return 8.0;
}


GraphicRing::GraphicRing() :
gHandleName("ring64"),
exRate(Random::FRand(0.4, 1.0)),
hue(Random::FRand(0.0, 1.0))
{
}

void GraphicRing::draw(Vector2 &pos){
	Draw::exrot(pos, exRate, eFrame, GraphHue::handled(gHandleName, hue), alpha);
}

double GraphicRing::getRadius(){
	return 32.0 * exRate;
}

GraphicOnCircle::GraphicOnCircle() :
objNum(Random::Rand(4, 8)),
firstAngle(Random::FRadRand()),
radius(Random::NormalDist(24, 24)),
exRate(Random::FRand(0.5, 1.5), Random::FRand(0.1, 1.0)),
angleEFrameRate(Random::FRand(0.01, 0.05) * Random::RandPM1()),
rotAngle(0.0),
gHandleName("circle32")
{
	if (Random::RandBool(0.2)){
		rotAngle += Random::FRadRand();
	}
}

void GraphicOnCircle::draw(Vector2 &pos){
	for (int i = 0; i < objNum; i++){
		double angle = 2 * PI / objNum * i + firstAngle + angleEFrameRate * eFrame;

		auto dpos = pos + Vector2::GetPolar(radius, angle);
		Draw::exrot3(dpos, Vector2(16, 16), exRate, angle + rotAngle, GraphHue::handled(gHandleName, hueKeeper.getHue(i, objNum)), alpha);
	}
}

double GraphicOnCircle::getRadius(){
	int x, y;
	GetGraphSize(GraphHue::handled(gHandleName, 0.1), &x, &y);
	return radius + 0.5 * x * exRate.x;
}

GraphicOnCircleRect::GraphicOnCircleRect() :
objNum(Random::Rand(4, 8)),
firstAngle(Random::FRadRand()),
radius(Random::FRand(24, 50)),
exRate(Random::FRand(0.5, 1.5), Random::FRand(0.1, 1.0)),
angleEFrameRate(Random::FRand(0.01, 0.05) * Random::RandPM1()),
rotAngle(PI / 4),
gHandleName("rect32")
{
	if (Random::Rand(100) < 20){
		rotAngle = 0.0;
	}
}

void GraphicOnCircleRect::draw(Vector2 &pos){
	for (int i = 0; i < objNum; i++){
		double angle = 2 * PI / objNum * i + firstAngle + angleEFrameRate * eFrame;

		auto dpos = pos + Vector2::GetPolar(radius, angle);
		Draw::exrot3(dpos, Vector2(16, 16), exRate, angle + rotAngle, GraphHue::handled(gHandleName, hueKeeper.getHue(i, objNum)), alpha);
	}
}

double GraphicOnCircleRect::getRadius(){
	int x, y;
	GetGraphSize(GraphHue::handled(gHandleName, 0.1), &x, &y);
	return radius + 0.5 * x * exRate.x;
}

GraphicOnCircleRTri::GraphicOnCircleRTri() :
objNum(Random::Rand(4, 12)),
firstAngle(Random::FRadRand()),
radius(Random::FRand(24, 50)),
exRate(Random::FRand(0.6, 1.5), Random::FRand(0.3, 1.0)),
angleEFrameRate(Random::FRand(0.01, 0.05) * Random::RandPM1()),
rotAngle(0.0),
gHandleName("r_tri16_32")
{
	if (Random::Rand(100) < 20){
		rotAngle = PI / 2;
	}
	if (Random::Rand(100) < 20){
		rotAngle = PI / 4;
	}
}

void GraphicOnCircleRTri::draw(Vector2 &pos){
	for (int i = 0; i < objNum; i++){
		double angle = 2 * PI / objNum * i + firstAngle + angleEFrameRate * eFrame;

		auto dpos = pos + Vector2::GetPolar(radius, angle);
		Draw::exrot3(dpos, Vector2(16, 16), exRate, angle + rotAngle, GraphHue::handled(gHandleName, hueKeeper.getHue(i, objNum)), alpha);
	}
}

double GraphicOnCircleRTri::getRadius(){
	int x, y;
	GetGraphSize(GraphHue::handled(gHandleName, 0.1), &x, &y);
	return radius + 0.5 * x * exRate.x;
}


GraphicOnCircleNoRotate::GraphicOnCircleNoRotate() :
objNum(Random::Rand(4, 8)),
firstAngle(Random::FRadRand()),
radius(Random::FRand(12, 44)),
angleEFrameRate(Random::FRand(0.01, 0.05) * Random::RandPM1()),
rotAngle(0.0),
gHandleName("lack_rect32")
{
	exRate = Vector2(1.0, 1.0) * Random::FRand(0.5, 1.0);
	if (Random::Rand(100) < 20){
		rotAngle += PI / 4;
	}
}

void GraphicOnCircleNoRotate::draw(Vector2 &pos){
	for (int i = 0; i < objNum; i++){
		double angle = 2 * PI / objNum * i + firstAngle + angleEFrameRate * eFrame;

		auto dpos = pos + Vector2::GetPolar(radius, angle);
		Draw::exrot3(dpos, Vector2(16, 16), exRate, 0.0, GraphHue::handled(gHandleName, hueKeeper.getHue(i, objNum)), alpha);
	}
}

double GraphicOnCircleNoRotate::getRadius(){
	int x, y;
	GetGraphSize(GraphHue::handled(gHandleName, 0.1), &x, &y);
	return radius + 0.5 * x * exRate.x;
}


IEnemy::IEnemy(Vector2 pos_) :
pos(pos_),
canShotPosY(450),
hp(100.0)
{
}


void IEnemy::isScreenOut(){
	if (!Func::IsAlivePos(pos)){
		IsDead = true;
	}
}
void IEnemy::checkHp(){
	if (hp < 0.0){
		Sound::playone("mybomb01");
		eff::make(pos, "EnemyDeadBomb");
		int score = mgr.scoreMgr_->addScoreEnemyKill();
		std::string str = "+" + std::to_string(score);
		mgr.effect_.add(std::make_shared<StrEf>(pos, str));
		IsDead = true;
	}
}


Enemy_::Enemy_(Vector2 pos_) :
IEnemy(pos_)
{
	//移動アルゴリズムを定義
	auto moverFac = [&]()->std::shared_ptr<IMover>{
		double r = Random::FRand(1.0);
		if (r < 0.1){
			return std::make_shared<MoverToPlayer>(pos_);
		}
		else if (r < 0.2){
			return std::make_shared<MoverToCenter>(pos_);
		}
		else if (r < 0.3){
			return std::make_shared<Mover3Pos>(pos_);
		}
		else{
			return std::make_shared<Mover1Pos>(pos_);
		}
	};
	mover = moverFac();

	//射撃アルゴリズムを定義
	auto weaponFac = [&]()->std::shared_ptr<IWeapon>{
		int r = Random::Rand(7);

		if (r == 0){
			return std::make_shared<WeaponToPlayer>(pos_);
		}
		else if (r == 1){
			return std::make_shared<WeaponAround>(pos_);
		}
		else if (r == 2){
			return std::make_shared<WeaponAroundSomeNum>(pos_);
		}
		else if (r == 3){
			return std::make_shared<WeaponAroundToPlayer>(pos_);
		}
		else if (r == 4){
			return std::make_shared<WeaponToPlayerSomeNum>(pos_);
		}
		else if (r == 5){
			return std::make_shared<WeaponToPlayerParallel>(pos_);
		}
		else if (r == 6){
			return std::make_shared<WeaponToPlayerNWay>(pos_);
		}
		else{
			return std::make_shared<WeaponAroundSinAngle>(pos_);
		}
	};
	weapon.emplace_back(weaponFac());

	//描画グラフィックを定義
	auto graphicFac = []()->std::shared_ptr<IGraphic>{
		int r = Random::Rand(3);
		if (r == 0){
			return std::make_shared<GraphicOnCircle>();
		}
		else if (r == 1){
			return std::make_shared<GraphicOnCircleRect>();
		}
		else if (r == 2){
			return std::make_shared<GraphicOnCircleRTri>();
		}
		else{
			return std::make_shared<GraphicOnCircleNoRotate>();
		}
	};
	graphic.emplace_back(graphicFac());
	if (Random::RandBool(0.4)){
		graphic.emplace_back(graphicFac());
	}

	if (Random::RandBool(0.1)){
		graphic.emplace_back(std::make_shared<GraphicRing>());
	}

	graphic.emplace_back(std::make_shared<GraphicCore>());

	//グラフィックから当たり判定を定義（円）
	double graphicRadius = 0.0;
	for (auto i = graphic.begin(); i < graphic.end(); i++){
		graphicRadius = std::max<double>(graphicRadius, (**i).getRadius());
	}
	col = std::make_shared<ColCircle>(pos, graphicRadius);
}

void Enemy_::update(){
	mover->update(pos);
	std::static_pointer_cast<ColCircle>(col)->pos = pos;

	if (pos.y < canShotPosY){
		for (auto i = weapon.begin(); i < weapon.end(); i++){
			(**i).update(pos);
		}
	}
	for (auto i = graphic.begin(); i < graphic.end(); i++){
		(**i).update();
	}
	isScreenOut();
	checkHp();
}

void Enemy_::draw(){
	for (auto i = graphic.begin(); i < graphic.end(); i++){
		(**i).draw(pos);
	}
	//Col::draw(col, 0xFF8888);
}



ResultEnemyEffect::ResultEnemyEffect(Vector2 pos_) :
IEnemy(pos_),
vel(Random::FRand(-1.0, 1.0), Random::FRand(1.0, 4.0))
{
	//描画グラフィックを定義
	auto graphicFac = []()->std::shared_ptr<IGraphic>{
		int r = Random::Rand(3);
		if (r == 0){
			return std::make_shared<GraphicOnCircle>();
		}
		else if (r == 1){
			return std::make_shared<GraphicOnCircleRect>();
		}
		else if (r == 2){
			return std::make_shared<GraphicOnCircleRTri>();
		}
		else{
			return std::make_shared<GraphicOnCircleNoRotate>();
		}
	};
	graphic.emplace_back(graphicFac());
	if (Random::RandBool(0.4)){
		graphic.emplace_back(graphicFac());
	}

	if (Random::RandBool(0.1)){
		graphic.emplace_back(std::make_shared<GraphicRing>());
	}

	graphic.emplace_back(std::make_shared<GraphicCore>());
}

void ResultEnemyEffect::update(){
	pos += vel;
	//遊び心（仮）
	if ((Input::mousePos() - pos).GetMagnitude() < 64.0){
		for (int i = 0; i < 3; i++){
			eff::make((Input::mousePos() + pos) * 0.5 + Random::RandInCircle(32.0), "CirBlank");
		}
		pos += (Input::mousePos() - pos).GetNormalized() * -2.0;
	}

	for (auto i = graphic.begin(); i < graphic.end(); i++){
		(**i).update();
	}
	isScreenOut();
}

void ResultEnemyEffect::draw(){
	for (auto i = graphic.begin(); i < graphic.end(); i++){
		(**i).draw(pos);
	}
}