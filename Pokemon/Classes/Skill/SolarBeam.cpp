#include "SolarBeam.h"

SolarBeam::SolarBeam()
{
}

SolarBeam::~SolarBeam()
{
}

void SolarBeam::Init()
{
	Skill::SetName("Solar Beam");
	Skill::SetType("Grass");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(4);
	Skill::SetPP(5);
}