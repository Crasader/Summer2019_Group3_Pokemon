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
	Skill::SetTypeName("Fire");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(2);
	Skill::SetCurrentPP(20);
}

