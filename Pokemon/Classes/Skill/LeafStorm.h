#pragma once
#include "Skill.h"

class LeafStorm : public Skill
{
public:
	LeafStorm();
	~LeafStorm();
	void Init() override;
	void Run(Vec2 position) override;
};