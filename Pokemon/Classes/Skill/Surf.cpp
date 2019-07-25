#include"Surf.h"

Surf::Surf()
{
	this->Init();
}

Surf::~Surf()
{
}

void Surf::Init()
{
	this->AddAnimation(109);
	this->SetScale(1.5);
	Skill::SetName("Surf");
	Skill::SetTypeName("Water");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_WATER);
	Skill::SetCurrentPP(10);
}