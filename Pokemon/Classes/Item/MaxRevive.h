#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Item.h"

using namespace cocos2d;

class MaxRevive : public Item
{
public:
	MaxRevive();
	~MaxRevive();
	void MaxRevivePokemon(Pokemon* pokemon);
private:
};