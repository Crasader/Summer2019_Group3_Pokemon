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
	this->SetAnimation(110);
	Skill::SetName("Tackle");
	Skill::SetTypeName("Normal");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(1);
	Skill::SetCurrentPP(35);
}