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
	Skill::SetTypeName("Grass");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_GRASS);
	Skill::SetCurrentPP(35);
}

