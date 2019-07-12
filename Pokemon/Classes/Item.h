#pragma once
#include "cocos2d.h"
#include "MyObject.h"

using namespace cocos2d;

class Item : public MyObject
{
public:
	Item();
	~Item();
	void Init(int id);
	int GetGold();
	string GetName();
	int GetType();
	void SetGold(int gold);
	void SetName(string name);
	void SetType(int type);
protected:
	int type;
	string name;
	int gold;
	vector<Item*> m_items;
};