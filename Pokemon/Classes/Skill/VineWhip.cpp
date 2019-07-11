#include"VineWhip.h"

VineWhip::VineWhip()
{
}

VineWhip::~VineWhip()
{
}

void VineWhip::Init()
{
	Skill::SetName("Vine Whip");
	Skill::SetType("Grass");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(4);
	Skill::SetPP(35);
}

