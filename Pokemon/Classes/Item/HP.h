#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "Pokemon.h"
using namespace cocos2d;

class HP : public Item
{
public:
	HP();
	~HP();
	virtual void ReviceHealth(Pokemon* pokemon) {};
protected:
	int HpRevice;
};
