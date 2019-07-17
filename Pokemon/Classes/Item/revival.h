#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "Pokemon.h"

using namespace cocos2d;

class Revival : public Item
{
public:
	Revival();
	~Revival();
	virtual void ReviceHealth(Pokemon* pokemon) {};
protected:
	int HpRevice;
	int Number;
};

