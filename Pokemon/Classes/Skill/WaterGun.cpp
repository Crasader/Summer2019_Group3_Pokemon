#include"WaterGun.h"

WaterGun::WaterGun()
{
}

WaterGun::~WaterGun()
{
}

void WaterGun::Init()
{
	Attack::SetName("Water Gun");
	Attack::SetType("Water");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(3);
	Attack::SetPP(35);
}

