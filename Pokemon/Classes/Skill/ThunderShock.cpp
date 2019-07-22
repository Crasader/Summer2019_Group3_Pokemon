#include"ThunderShock.h"

ThunderShock::ThunderShock()
{
}

ThunderShock::~ThunderShock()
{
}

void ThunderShock::Init()
{
	Skill::SetName("Thunder Shock");
	Skill::SetTypeName("Electric");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_ELECTRIC);
	Skill::SetCurrentPP(35);
}

