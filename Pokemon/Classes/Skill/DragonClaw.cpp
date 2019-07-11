#include"DragonClaw.h"

DragonClaw::DragonClaw()
{
}

DragonClaw::~DragonClaw()
{
}

void DragonClaw::Init()
{
	Skill::SetName("DragonClaw");
	Skill::SetType("Dragon");
	Skill::SetPower(100);
	Skill::SetMaxPP(10);
	Skill::SetIdType(7);
	Skill::SetPP(10);
}

