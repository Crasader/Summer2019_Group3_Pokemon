#include"Bubble.h"

Bubble::Bubble()
{
}

Bubble::~Bubble()
{
}

void Bubble::Init()
{
	Attack::SetName("Bubble");
	Attack::SetType("Water");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(3);
	Attack::SetPP(35);
}

