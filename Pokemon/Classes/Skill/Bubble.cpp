#include "Bubble.h"

Bubble::Bubble()
{
}

Bubble::~Bubble()
{
}

void Bubble::Init()
{
	Skill::SetName("Bubble");
	Skill::SetTypeName("Water");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(3);
	Skill::SetCurrentPP(35);
}