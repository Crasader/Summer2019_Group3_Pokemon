#include"SolarBeam.h"

SolarBeam::SolarBeam()
{
}

SolarBeam::~SolarBeam()
{
}

void SolarBeam::Init()
{
	Attack::SetName("Solar Beam");
	Attack::SetType("Grass");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(4);
	Attack::SetPP(5);
}

