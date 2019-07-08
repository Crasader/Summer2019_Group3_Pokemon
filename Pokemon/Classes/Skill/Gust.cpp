#include"Gust.h"

Gust::Gust()
{
}

Gust::~Gust()
{
}

void Gust::Init()
{
	Attack::SetName("Gust");
	Attack::SetType("Flying");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(6);
	Attack::SetPP(20);
}

