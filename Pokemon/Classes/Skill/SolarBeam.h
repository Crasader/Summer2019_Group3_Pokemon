#pragma once
#include "Skill.h"

class SolarBeam : public Skill
{
public:
	SolarBeam();
	~SolarBeam();
	void Init() override;
};