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
	Skill::SetName("Peck");
	Skill::SetType("Flying");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(6);
	Skill::SetPP(35);
}

