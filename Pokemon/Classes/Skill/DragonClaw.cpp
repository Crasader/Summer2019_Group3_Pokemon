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
	Skill::SetTypeName("Dragon");
	Skill::SetPower(100);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_DRAGON);
	Skill::SetCurrentPP(10);
}