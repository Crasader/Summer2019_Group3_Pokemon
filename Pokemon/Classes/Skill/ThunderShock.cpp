#include"ThunderShock.h"

ThunderShock::ThunderShock()
{
	this->Init();
}

ThunderShock::~ThunderShock()
{
}

void ThunderShock::Init()
{
	Attack::SetName("Thunder Shock");
	Attack::SetType("Electric");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(5);
	Attack::SetPP(35);
}

