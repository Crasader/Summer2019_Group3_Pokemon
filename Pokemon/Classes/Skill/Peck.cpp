#include "Peck.h"

Peck::Peck()
{
	this->Init();
}

Peck::~Peck()
{
}

void Peck::Init()
{
	this->AddAnimation(103);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(2);
	Skill::SetName("Peck");
	Skill::SetTypeName("Flying");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(35);
}