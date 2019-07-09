#include"FireBlast.h"

FireBlast::FireBlast()
{
}

FireBlast::~FireBlast()
{
}

void FireBlast::Init()
{
	Attack::SetName("Fire Blast");
	Attack::SetType("Fire");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(2);
	Attack::SetPP(10);
}

