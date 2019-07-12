#include"ThunderShock.h"

ThunderShock::ThunderShock()
{
	this->Init();
}

ThunderShock::~ThunderShock()
{
}

void ThunderShock::Init()
{
	Skill::SetName("Thunder Shock");
	Skill::SetType("Electric");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(5);
	Skill::SetPP(35);
}

