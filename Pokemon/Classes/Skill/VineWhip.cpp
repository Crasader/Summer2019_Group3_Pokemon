#include"VineWhip.h"

VineWhip::VineWhip()
{
}

VineWhip::~VineWhip()
{
}

void VineWhip::Init()
{
	Attack::SetName("Vine Whip");
	Attack::SetType("Grass");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(4);
	Attack::SetPP(35);
}

