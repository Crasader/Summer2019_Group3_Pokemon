#include"HydroPump.h"

HydroPump::HydroPump()
{
}

HydroPump::~HydroPump()
{
}

void HydroPump::Init()
{
	Skill::SetName("HydroPump");
	Skill::SetType("Water");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(3);
	Skill::SetPP(5);
}

