#include"VineWhip.h"

VineWhip::VineWhip()
{
	this->Init();
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
	Skill::SetIdType(4);
	Skill::SetCurrentPP(35);
}

