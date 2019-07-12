#include"WaterGun.h"

WaterGun::WaterGun()
{
	this->Init();
}

WaterGun::~WaterGun()
{
}

void WaterGun::Init()
{
	Skill::SetName("Water Gun");
	Skill::SetType("Water");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(3);
	Skill::SetPP(20);
}

