#pragma once
#include "Skill.h"

class Bubble : public Skill
{
public:
	Bubble();
	~Bubble();
	void Init() override;
	void Run(Vec2 position) override;
};