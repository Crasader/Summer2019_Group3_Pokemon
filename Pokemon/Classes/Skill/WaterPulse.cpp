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
	Skill::SetTypeName("Water");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(3);
	Skill::SetCurrentPP(20);
}

