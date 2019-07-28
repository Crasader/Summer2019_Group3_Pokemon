#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "Pokemon.h"

class MaxPotion : public Item
{
public:
	MaxPotion();
	~MaxPotion();
	void ReviceHealthPokemon(Pokemon * pokemon);
private:
};