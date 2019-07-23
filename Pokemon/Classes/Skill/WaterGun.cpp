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
	Skill::SetTypeName("Water");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(3);
	Skill::SetCurrentPP(35);
}

