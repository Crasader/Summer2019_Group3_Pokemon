#include "QuickAttack.h"

QuickAttack::QuickAttack()
{
	this->Init();
}

QuickAttack::~QuickAttack()
{
}

void QuickAttack::Init()
{
	this->AddAnimation(104);
	this->SetScale(1.5);
	Skill::SetName("Quick Attack");
	Skill::SetTypeName("Normal");
	Skill::SetPower(50);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_NORMAL);
	Skill::SetCurrentPP(20);
}