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
	void SetGold(int gold);
	void SetName(string name);
	int GetNumber();
	void SetNumber(int index);
protected:
	string name;
	int gold;
	vector<Item*> m_items;
	int Number;
};