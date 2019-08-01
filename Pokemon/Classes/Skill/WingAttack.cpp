#include "WingAttack.h"

WingAttack::WingAttack()
{
	this->Init();
}

WingAttack::~WingAttack()
{
}

void WingAttack::Init()
{
	this->AddAnimation(117);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(0.8);
	Skill::SetName("Wing Attack");
	Skill::SetTypeName("Flying");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(10);
}