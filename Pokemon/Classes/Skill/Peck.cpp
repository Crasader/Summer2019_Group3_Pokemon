#include"Peck.h"

Peck::Peck()
{
}

Peck::~Peck()
{
}

void Peck::Init()
{
	Skill::SetName("Peck");
	Skill::SetTypeName("Flying");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(35);
}

