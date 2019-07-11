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
	Skill::SetType("Fire");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(2);
	Skill::SetPP(5);
}

