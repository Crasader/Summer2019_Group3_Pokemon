#pragma once
#include "cocos2d.h"
#include "MyObject.h"

using namespace cocos2d;

class Item : public MyObject
{
public:
	Item();
	~Item();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
protected:
	int type;
	vector<Item*> m_items;
};