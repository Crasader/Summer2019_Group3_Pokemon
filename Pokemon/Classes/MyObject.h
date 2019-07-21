#pragma once
#include "cocos2d.h"
#include "ResourceManager.h"
using namespace cocos2d;

class MyObject
{
public:
	static const int TYPE_NORMAL = 1;
	static const int TYPE_FIRE = 2;
	static const int TYPE_WATER = 3;
	static const int TYPE_GRASS = 4;
	static const int TYPE_ELECTRIC = 5;
	static const int TYPE_FLYING = 6;
	static const int TYPE_DRAGON = 7;
protected:
	Sprite* m_spriteFront;
	Sprite* m_spriteBack;
public:
	MyObject();
	~MyObject();
	virtual void Init() {};
	virtual void Init(int id_front, int id_back) {};
	virtual void Update(float deltaTime) {};
	Sprite* GetSpriteFront();
	Sprite* GetSpriteBack();
	void SetSprite(int id);
};