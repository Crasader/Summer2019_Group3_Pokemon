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
	Attack::SetName("DragonClaw");
	Attack::SetType("Dragon");
	Attack::SetPower(100);
	Attack::SetMaxPP(10);
	Attack::SetIdType(7);
	Attack::SetPP(10);
}

