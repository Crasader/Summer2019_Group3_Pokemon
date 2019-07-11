#include"Thunderbolt.h"

Thunderbolt::Thunderbolt()
{
	this->Init();
}

Thunderbolt::~Thunderbolt()
{
}

void Thunderbolt::Init()
{
	Attack::SetName("Thunderbolt");
	Attack::SetType("Electric");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(5);
	Attack::SetPP(10);
}

