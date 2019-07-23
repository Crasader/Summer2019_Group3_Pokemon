#include"BlastBurn.h"

BlastBurn::BlastBurn()
{
	this->Init();
}

BlastBurn::~BlastBurn()
{
}

void BlastBurn::Init()
{
	Skill::SetTypeName("Fire");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(2);
	Skill::SetCurrentPP(5);
}
