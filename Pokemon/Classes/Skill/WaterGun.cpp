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
	Attack::SetName("Water Gun");
	Attack::SetType("Water");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(3);
	Attack::SetPP(20);
}

