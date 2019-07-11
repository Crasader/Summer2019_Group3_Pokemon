#include"Bite.h"

Bite::Bite()
{
	this->Init();
}

Bite::~Bite()
{
}

void Bite::Init()
{
	Attack::SetName("Bite");
	Attack::SetType("Normal");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(1);
	Attack::SetPP(10);
}

