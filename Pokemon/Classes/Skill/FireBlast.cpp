#include"FireBlast.h"

FireBlast::FireBlast()
{
}

FireBlast::~FireBlast()
{
}

void FireBlast::Init()
{
	Skill::SetName("Fire Blast");
	Skill::SetType("Fire");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(2);
	Skill::SetPP(10);
}

