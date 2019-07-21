#pragma once
#include "cocos2d.h"
#include "Item\HP.h"
using namespace cocos2d;

class Potion : public HP
{
public:
	Potion();
	~Potion();
	void ReviceHealth(Pokemon* pokemon) override;
};
