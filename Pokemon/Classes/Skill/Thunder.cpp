#include"Thunder.h"

Thunder::Thunder()
{
	this->Init();
}

Thunder::~Thunder()
{
}

void Thunder::Init()
{
	Skill::SetName("Thunder");
	Skill::SetType("Electric");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(5);
	Skill::SetPP(5);
}

