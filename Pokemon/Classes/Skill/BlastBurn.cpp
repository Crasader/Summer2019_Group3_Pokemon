#include "BlastBurn.h"

BlastBurn::BlastBurn()
{
	this->Init();
}

BlastBurn::~BlastBurn()
{
}

void BlastBurn::Init()
{
	this->AddAnimation(91);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(1.5);
	Skill::SetName("Blast Burn");
	Skill::SetTypeName("Fire");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_FIRE);
	Skill::SetCurrentPP(5);
}