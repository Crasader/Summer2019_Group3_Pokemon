#include"Bite.h"

Bite::Bite()
{
	this->Init();
}

Bite::~Bite()
{
}

void Bite::Init()
{
	this->SetAnimation(90);
	Skill::SetName("Bite");
	Skill::SetTypeName("Normal");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(1);
	Skill::SetCurrentPP(10);
}