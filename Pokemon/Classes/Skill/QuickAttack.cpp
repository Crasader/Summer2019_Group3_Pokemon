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
	Skill::SetType("Normal");
	Skill::SetPower(50);
	Skill::SetMaxPP(20);
	Skill::SetIdType(1);
	Skill::SetPP(20);
}

