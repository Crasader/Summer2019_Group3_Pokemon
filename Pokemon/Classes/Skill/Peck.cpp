#include"Peck.h"

Peck::Peck()
{
	this->Init();
}

Peck::~Peck()
{
}

void Peck::Init()
{
	Attack::SetName("Peck");
	Attack::SetType("Flying");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(6);
	Attack::SetPP(35);
}

