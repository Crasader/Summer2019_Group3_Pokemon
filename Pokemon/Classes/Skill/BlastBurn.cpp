#include"BlastBurn.h"

BlastBurn::BlastBurn()
{
}

BlastBurn::~BlastBurn()
{
}

void BlastBurn::Init()
{
	Skill::SetName("BlastBurn");
	Skill::SetTypeName("Fire");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_FIRE);
	Skill::SetCurrentPP(5);
}