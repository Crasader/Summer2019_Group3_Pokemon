#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "Attack.h"
using namespace cocos2d;

class PP : public Item
{
public:
	PP();
	~PP();
	void ReviceSkill(Attack* skill);
};

