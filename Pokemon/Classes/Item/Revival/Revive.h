#pragma once
#include "cocos2d.h"
#include "Item\Revival.h"
using namespace cocos2d;

class Revive : public Revival
{
public:
	Revive();
	~Revive();
	void ReviceHealth(Pokemon* pokemon);
};
