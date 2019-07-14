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
	this->AddAnimate(90);
	Skill::SetName("Bite");
	Skill::SetType("Normal");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(1);
	Skill::SetPP(10);
}