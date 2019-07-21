#include"Scratch.h"

Scratch::Scratch()
{
	this->Init();
}

Scratch::~Scratch()
{
}

void Scratch::Init()
{
	this->SetAnimation(106);
	this->SetScale(1.5);
	Skill::SetName("Scratch");
	Skill::SetTypeName("Normal");
	Skill::SetPower(60);
	Skill::SetMaxPP(15);
	Skill::SetIdType(1);
	Skill::SetCurrentPP(10);
}