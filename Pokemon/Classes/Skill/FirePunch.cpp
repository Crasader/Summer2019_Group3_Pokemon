#include"FirePunch.h"

FirePunch::FirePunch()
{
}

FirePunch::~FirePunch()
{
}

void FirePunch::Init()
{
	Attack::SetName("Fire Punch");
	Attack::SetType("Fire");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(2);
	Attack::SetPP(20);
}

