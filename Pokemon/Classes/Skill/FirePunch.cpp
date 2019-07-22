#include"FirePunch.h"

FirePunch::FirePunch()
{
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
	Skill::SetIdType(MyObject::TYPE_FIRE);
	Skill::SetCurrentPP(20);
}

