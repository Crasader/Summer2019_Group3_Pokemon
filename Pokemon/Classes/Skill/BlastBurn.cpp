#include"BlastBurn.h"

BlastBurn::BlastBurn()
{
	this->Init();
}

BlastBurn::~BlastBurn()
{
}

void BlastBurn::Init()
{
	Attack::SetName("BlastBurn");
	Attack::SetType("Fire");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(2);
	Attack::SetPP(5);
}

