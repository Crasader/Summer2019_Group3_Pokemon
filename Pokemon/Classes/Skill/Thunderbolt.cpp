#include "Thunderbolt.h"

Thunderbolt::Thunderbolt()
{
	this->Init();
}

Thunderbolt::~Thunderbolt()
{
}

void Thunderbolt::Init()
{
	this->AddAnimation(112);
	this->GetAnimation()->setDelayPerUnit(0.15);
	this->SetScale(2);
	Skill::SetName("Thunderbolt");
	Skill::SetTypeName("Electric");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_ELECTRIC);
	Skill::SetCurrentPP(10);
}