#include "ThunderShock.h"

ThunderShock::ThunderShock()
{
	this->Init();
}

ThunderShock::~ThunderShock()
{
}

void ThunderShock::Init()
{
	this->AddAnimation(113);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(1.5);
	Skill::SetName("Thunder Shock");
	Skill::SetTypeName("Electric");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_ELECTRIC);
	Skill::SetCurrentPP(35);
}