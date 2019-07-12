#pragma once
#include "cocos2d.h"
#include "Item\HP.h"
using namespace cocos2d;

class SuperPotion : public HP
{
public:
	SuperPotion();
	~SuperPotion();
	void ReviceHealth(Pokemon* pokemon) override;
};
