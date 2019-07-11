#include"Fly.h"

Fly::Fly()
{
}

Fly::~Fly()
{
}

void Fly::Init()
{
	Skill::SetName("Fly");
	Skill::SetType("Flying");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(6);
	Skill::SetPP(5);
}

