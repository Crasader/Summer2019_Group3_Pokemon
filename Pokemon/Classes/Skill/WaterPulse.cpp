#include"WaterPulse.h"

WaterPulse::WaterPulse()
{
}

WaterPulse::~WaterPulse()
{
}

void WaterPulse::Init()
{
	Skill::SetName("Water Pulse");
	Skill::SetType("Water");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(3);
	Skill::SetPP(20);
}

