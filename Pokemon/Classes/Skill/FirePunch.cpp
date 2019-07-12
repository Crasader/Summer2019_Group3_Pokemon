#include"FirePunch.h"

FirePunch::FirePunch()
{
	this->Init();
}

FirePunch::~FirePunch()
{
}

void FirePunch::Init()
{
	Skill::SetName("Fire Punch");
	Skill::SetType("Fire");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(2);
	Skill::SetPP(20);
}

