#include"Tackle.h"

Tackle::Tackle()
{
	this->Init();
}

Tackle::~Tackle()
{
}

void Tackle::Init()
{
	Attack::SetName("Tackle");
	Attack::SetType("Normal");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(1);
	Attack::SetPP(35);
}

