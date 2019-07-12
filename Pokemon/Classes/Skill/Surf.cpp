#include"Surf.h"

Surf::Surf()
{
	this->Init();
}

Surf::~Surf()
{
}

void Surf::Init()
{
	Skill::SetName("Surf");
	Skill::SetType("Water");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(3);
	Skill::SetPP(5);
}

