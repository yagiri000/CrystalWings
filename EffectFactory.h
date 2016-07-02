#pragma once

#include <DxLib.h>

#include "Effects.h"
#include "Vector2.h"

class EffectFactory
{
public:
	EffectFactory();
	static std::shared_ptr<IEffect> make(Vector2 pos, std::string key);
	static std::shared_ptr<IEffect> make(Vector2 pos, std::string key, int makeNum);
	/*
	template <typename T>
	static std::shared_ptr<IEffect> maket(Vector2 pos){
		std::shared_ptr<IEffect> tmp = nullptr;
		tmp = std::make_shared<T>(pos.x, pos.y);
		mgr.effect_.add(tmp);
		return tmp;
	}
	*/
};

using eff = EffectFactory;
