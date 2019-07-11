#include"Scratch.h"

Scratch::Scratch()
{
}

Scratch::~Scratch()
{
}

void Scratch::Init()
{
	Skill::SetName("Scratch");
	Skill::SetType("Normal");
	Skill::SetPower(60);
	Skill::SetMaxPP(15);
	Skill::SetIdType(1);
	Skill::SetPP(10);
}

