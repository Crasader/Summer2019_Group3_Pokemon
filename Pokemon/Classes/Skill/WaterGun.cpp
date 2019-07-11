#include"WaterGun.h"

WaterGun::WaterGun()
{
}

WaterGun::~WaterGun()
{
}

void WaterGun::Init()
{
	Skill::SetName("Water Gun");
	Skill::SetType("Water");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(3);
	Skill::SetPP(35);
}

