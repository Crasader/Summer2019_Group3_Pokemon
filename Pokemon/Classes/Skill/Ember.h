#pragma once
#include"cocos2d.h"
#include "Skill.h"

class Ember : public Skill
{
public:
	Ember();
	~Ember();
	void Init();
	void Run(Vec2 position) override;
};