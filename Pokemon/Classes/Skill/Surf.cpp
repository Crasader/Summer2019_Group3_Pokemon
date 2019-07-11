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
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(3);
	Attack::SetPP(5);
}

