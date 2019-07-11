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
	Attack::SetName("Vine Whip");
	Attack::SetType("Grass");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(4);
	Attack::SetPP(35);
}

