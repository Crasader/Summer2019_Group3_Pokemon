#include"Fly.h"

Fly::Fly()
{
	this->Init();
}

Fly::~Fly()
{
}

void Fly::Init()
{
	Skill::SetName("Fly");
	Skill::SetTypeName("Flying");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(6);
	Skill::SetCurrentPP(5);
}

