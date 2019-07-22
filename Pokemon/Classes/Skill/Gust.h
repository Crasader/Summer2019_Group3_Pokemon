#pragma once
#include"cocos2d.h"
#include "Skill.h"

class Gust : public Skill
{
public:
	Gust();
	~Gust();
	void Init();
	void Run(Vec2 position) override;
};