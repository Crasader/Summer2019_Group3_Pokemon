#include"QuickAttack.h"

QuickAttack::QuickAttack()
{
	this->Init();
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
	Skill::SetIdType(1);
	Skill::SetCurrentPP(20);
}

