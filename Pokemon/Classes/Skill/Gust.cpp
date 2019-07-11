#include"Gust.h"

Gust::Gust()
{
}

Gust::~Gust()
{
}

void Gust::Init()
{
	Skill::SetName("Gust");
	Skill::SetType("Flying");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(6);
	Skill::SetPP(20);
}

