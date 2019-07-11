#include"DragonCut.h"

DragonCut::DragonCut()
{
}

DragonCut::~DragonCut()
{
}

void DragonCut::Init()
{
	Skill::SetName("Dragon Cut");
	Skill::SetType("Dragon");
	Skill::SetPower(50);
	Skill::SetMaxPP(30);
	Skill::SetIdType(7);
	Skill::SetPP(30);
}

