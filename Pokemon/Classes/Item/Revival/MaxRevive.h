#pragma once
#include "cocos2d.h"
#include "Item\Revival.h"
#include "Pokemon.h"

using namespace cocos2d;

class MaxRevive : public Revival
{
public:
	MaxRevive();
	~MaxRevive();
	void ReviceHealth(Pokemon* pokemon);
};

