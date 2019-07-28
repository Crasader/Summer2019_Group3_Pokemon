#pragma once
#include "cocos2d.h"
#include "Skill.h"

class LeechSeed : public Skill
{
public:
	LeechSeed();
	~LeechSeed();
	void Init();
	void Run(Vec2 position) override;
};