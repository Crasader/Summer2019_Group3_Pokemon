#include"Fly.h"

Fly::Fly()
{
}

Fly::~Fly()
{
}

void Fly::Init()
{
	Attack::SetName("Fly");
	Attack::SetType("Flying");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(6);
	Attack::SetPP(5);
}

