#include"Thunder.h"

Thunder::Thunder()
{
	this->Init();
}

Thunder::~Thunder()
{
}

void Thunder::Init()
{
	Attack::SetName("Thunder");
	Attack::SetType("Electric");
	Attack::SetPower(100);
	Attack::SetMaxPP(5);
	Attack::SetIdType(5);
	Attack::SetPP(5);
}

