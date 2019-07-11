#include"WingAttack.h"

WingAttack::WingAttack()
{
}

WingAttack::~WingAttack()
{
}

void WingAttack::Init()
{
	Skill::SetName("Wing Attack");
	Skill::SetType("Flying");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(6);
	Skill::SetPP(10);
}

