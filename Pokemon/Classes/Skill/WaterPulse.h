#pragma once
#include "cocos2d.h"
#include "Skill.h"

class WaterPulse : public Skill
{
public:
	WaterPulse();
	~WaterPulse();
	void Init();
	void Run(Vec2 position) override;
};
