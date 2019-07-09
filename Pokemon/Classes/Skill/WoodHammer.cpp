#include"WoodHammer.h"

WoodHammer::WoodHammer()
{
}

WoodHammer::~WoodHammer()
{
}

void WoodHammer::Init()
{
	Attack::SetName("Wood Hammer");
	Attack::SetType("Grass");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(4);
	Attack::SetPP(5);
}

