#include"WoodHammer.h"

WoodHammer::WoodHammer()
{
}

WoodHammer::~WoodHammer()
{
}

void WoodHammer::Init()
{
	Skill::SetName("Wood Hammer");
	Skill::SetType("Grass");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(4);
	Skill::SetPP(5);
}

