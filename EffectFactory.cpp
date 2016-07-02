#include "GameMgr.h"
#include "EffectFactory.h"
#include <memory>

/*if (Input::keydown(250)){
mgr.effect_.add(std::make_shared<MFSet_CircleBrust>(400, 300, [](double x, double y){
mgr.effect_.add(std::make_shared<bomb>(x, y));
}));
}
if (Input::keynow(KEY_INPUT_Z)){
eff::make(Input::mousePos(), "fire");
}*/


EffectFactory::EffectFactory()
{
}


std::shared_ptr<IEffect> EffectFactory::make(Vector2 pos, std::string key){
	std::shared_ptr<IEffect> tmp = nullptr;

	if (0){}
	else if (key == "fire"){ tmp = std::make_shared<fire>(pos); }
	else if (key == "slash"){ tmp = std::make_shared<slash>(pos); }
	else if (key == "bomb"){ tmp = std::make_shared<bomb>(pos); }
	else if (key == "CirBlank"){ tmp = std::make_shared<CirBlank>(pos); }
	else if (key == "BoxBlank"){ tmp = std::make_shared<BoxBlank>(pos); }
	else if (key == "PlayerDeadBomb"){ tmp = std::make_shared<PlayerDeadBomb>(pos); }
	else if (key == "PlayerTrail"){ tmp = std::make_shared<PlayerTrail>(pos); }
	else if (key == "Trail"){ tmp = std::make_shared<Trail>(pos); }
	else if (key == "EnemyDeadBomb"){ tmp = std::make_shared<EnemyDeadBomb>(pos); }
	else if (key == "Debri"){ tmp = std::make_shared<Debri>(pos); }
	else if (key == "TitleEf"){ tmp = std::make_shared<TitleEf>(pos); }
	else if (key == "BombSplash"){ tmp = std::make_shared<BombSplash>(pos); }
	else if (key == "BombRetro"){ tmp = std::make_shared<BombRetro>(pos); }
	
	mgr.effect_.add(tmp); 
	return tmp;
}


std::shared_ptr<IEffect> EffectFactory::make(Vector2 pos, std::string key, int makeNum){
	std::shared_ptr<IEffect> tmp = nullptr;
	for (int i = 0; i < makeNum; i++){
		tmp = make(pos, key);
	}
	return tmp;
}
