#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Item.h"

using namespace cocos2d;

class Revive : public Item
{
public:
	Revive();
	~Revive();
	void RevivePokemon(Pokemon* pokemon);
private:
};