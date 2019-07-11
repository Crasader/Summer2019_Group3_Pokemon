#pragma once
#include "cocos2d.h"
class Model
{
public:
	Model();
	~Model();
	void setPosition(cocos2d::Vec2 pos);
	void setScale(float scale);
	cocos2d::Vec2 getPosition();
	cocos2d::Size getContentSize();
protected:
	cocos2d::Sprite* m_sprite;

};

