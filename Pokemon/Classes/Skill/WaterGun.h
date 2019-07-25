#pragma once
#include "cocos2d.h"
#include "Skill.h"

class WaterGun : public Skill
{
public:
	WaterGun();
	~WaterGun();
	void Init();
	void Run(Vec2 position) override;
};