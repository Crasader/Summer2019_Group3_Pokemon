#include"HydroPump.h"

HydroPump::HydroPump()
{
}

HydroPump::~HydroPump()
{
}

void HydroPump::Init()
{
	Attack::SetName("HydroPump");
	Attack::SetType("Water");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(3);
	Attack::SetPP(5);
}

