#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "Pokemon.h"

class SuperPotion : public Item
{
public:
	SuperPotion();
	~SuperPotion();
	void ReviceHealthPokemon(Pokemon *pokemon);
private:
	int hpRevice;
};