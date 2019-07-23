#pragma once
#include"cocos2d.h"
#include "Skill.h"

class EnergyBall : public Skill
{
public:
	EnergyBall();
	~EnergyBall();
	void Init();
	void Run(Vec2 position) override;
};