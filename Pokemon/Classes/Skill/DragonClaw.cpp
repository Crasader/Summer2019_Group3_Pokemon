#include"DragonClaw.h"

DragonClaw::DragonClaw()
{
	this->Init();
}

DragonClaw::~DragonClaw()
{
}

void DragonClaw::Init()
{
	this->AddAnimation(95);
	this->SetScale(1.5);
	Skill::SetName("DragonClaw");
	Skill::SetType("Dragon");
	Skill::SetPower(100);
	Skill::SetMaxPP(10);
	Skill::SetIdType(7);
	Skill::SetPP(10);
}