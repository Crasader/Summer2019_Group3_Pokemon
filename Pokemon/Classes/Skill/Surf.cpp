#include"Surf.h"

Surf::Surf()
{
}

Surf::~Surf()
{
}

void Surf::Init()
{
	Attack::SetName("Surf");
	Attack::SetType("Water");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(3);
	Attack::SetPP(10);
}

