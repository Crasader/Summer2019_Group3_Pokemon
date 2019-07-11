#pragma once
#include "cocos2d.h"
#include "ResourceManager.h"
using namespace cocos2d;

class MyObject
{
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