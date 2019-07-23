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
	this->SetAnimation(95);
	this->SetScale(1.5);
	Skill::SetName("DragonClaw");
	Skill::SetTypeName("Dragon");
	Skill::SetPower(100);
	Skill::SetMaxPP(10);
	Skill::SetIdType(7);
	Skill::SetCurrentPP(10);
}
