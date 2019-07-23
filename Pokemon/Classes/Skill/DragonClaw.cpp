#include "DragonClaw.h"

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
	this->GetAnimation()->setDelayPerUnit(0.1);
	Skill::SetName("Dragon Claw");
	Skill::SetTypeName("Dragon");
	Skill::SetPower(100);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_DRAGON);
	Skill::SetCurrentPP(10);
}