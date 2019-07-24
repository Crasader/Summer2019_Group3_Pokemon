#pragma once
#include "Bag.h"
#include "MyObject.h"
#include "cocos2d.h"
#include <list>
#include "Pokemon.h"
USING_NS_CC;
using namespace std;
class Trainer : public MyObject
{
private:
	Animation* up;
	Animation* down;
	Animation* left;
	Animation* right;
public: 
	Trainer();
	Trainer(cocos2d::Layer* layer);
	~Trainer();
	void Init(cocos2d::Layer* layer);
	void walkLeft();
	void walkRight();
	void walkUp();
	void walkDown();
};

