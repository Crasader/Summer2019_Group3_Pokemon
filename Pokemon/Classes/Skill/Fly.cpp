#include "Fly.h"

Fly::Fly()
{
}

Fly::~Fly()
{
}

void Fly::Init()
{
	Skill::SetName("Fly");
	Skill::SetTypeName("Flying");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(5);
}