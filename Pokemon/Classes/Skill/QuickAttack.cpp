#include"QuickAttack.h"

QuickAttack::QuickAttack()
{
}

QuickAttack::~QuickAttack()
{
}

void QuickAttack::Init()
{
	Skill::SetName("Quick Attack");
	Skill::SetTypeName("Normal");
	Skill::SetPower(50);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_NORMAL);
	Skill::SetCurrentPP(20);
}

