#pragma once
#include"cocos2d.h"
#include "Skill.h"

class Thunder : public Skill
{
public:
	Thunder();
	~Thunder();
	void Init();
	void Run(Vec2 position) override;
};
