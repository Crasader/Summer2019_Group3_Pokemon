#include"Surf.h"

Surf::Surf()
{
}

Surf::~Surf()
{
}

void Surf::Init()
{
	Skill::SetName("Surf");
	Skill::SetType("Water");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(3);
	Skill::SetPP(10);
}

