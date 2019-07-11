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
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(3);
	Attack::SetPP(10);
}

