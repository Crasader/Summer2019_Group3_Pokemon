#include "Fly.h"

Fly::Fly()
{
	this->Init();
}

Fly::~Fly()
{
}

void Fly::Init()
{
	this->AddAnimation(101);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(1.5);
	Skill::SetName("Fly");
	Skill::SetTypeName("Flying");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(5);
}