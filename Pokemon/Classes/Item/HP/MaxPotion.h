#pragma once
#include "cocos2d.h"
#include "Item\HP.h"
using namespace cocos2d;

class MaxPotion : public HP
{
public:
	MaxPotion();
	~MaxPotion();
	void ReviceHealth(Pokemon* pokemon) override;
};
