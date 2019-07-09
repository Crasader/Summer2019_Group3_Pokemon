#include"WaterPulse.h"

WaterPulse::WaterPulse()
{
}

WaterPulse::~WaterPulse()
{
}

void WaterPulse::Init()
{
	Attack::SetName("Water Pulse");
	Attack::SetType("Water");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(3);
	Attack::SetPP(20);
}

