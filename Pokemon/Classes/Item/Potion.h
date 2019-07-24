#pragma once
#include "cocos2d.h"
#include "item.h"
#include "Pokemon.h"

class Potion: public Item
{
public:
	Potion();
	~Potion();
	void ReviceHealthPokemon(Pokemon *pokemon);
private:
	int hpRevice;
};