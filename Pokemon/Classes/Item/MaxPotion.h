#pragma once
#include "cocos2d.h"
#include "item.h"
#include "Pokemon.h"

class MaxPotion : public Item
{
public:
	MaxPotion();
	~MaxPotion();
	void ReviceHealthPokemon(Pokemon * pokemon);
private:
};