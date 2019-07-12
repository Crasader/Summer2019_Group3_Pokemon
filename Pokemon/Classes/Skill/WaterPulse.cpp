#include"WaterPulse.h"

WaterPulse::WaterPulse()
{
	this->Init();
}

WaterPulse::~WaterPulse()
{
}

void WaterPulse::Init()
{
	Skill::SetName("Water Pulse");
	Skill::SetType("Water");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(3);
	Skill::SetPP(10);
}

