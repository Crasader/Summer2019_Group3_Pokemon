#include"Thunderbolt.h"

Thunderbolt::Thunderbolt()
{
}

Thunderbolt::~Thunderbolt()
{
}

void Thunderbolt::Init()
{
	Skill::SetName("Thunderbolt");
	Skill::SetTypeName("Electric");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(5);
	Skill::SetCurrentPP(10);
}

