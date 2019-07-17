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
	this->AddAnimation(110);
	Skill::SetName("Tackle");
	Skill::SetType("Normal");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(1);
	Skill::SetPP(35);
}

