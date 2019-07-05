#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyObject
{
protected:
	Sprite* m_sprite;
public:
	MyObject();
	~MyObject();
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	Sprite* GetSprite();
};

