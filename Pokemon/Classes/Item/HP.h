#pragma once
#include "cocos2d.h"
#include "Item.h"
using namespace cocos2d;

class HP : public Item
{
public:
	HP();
	~HP();
protected:
	int HpRevice;
};
