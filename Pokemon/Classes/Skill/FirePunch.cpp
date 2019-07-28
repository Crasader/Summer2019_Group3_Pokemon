#include "FirePunch.h"

FirePunch::FirePunch()
{
	this->Init();
}

FirePunch::~FirePunch()
{
}

void FirePunch::Init()
{
	this->AddAnimation(100);
	this->SetScale(1.5);
	Skill::SetName("Fire Punch");
	Skill::SetTypeName("Fire");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_FIRE);
	Skill::SetCurrentPP(20);
}