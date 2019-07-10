#include"DragonCut.h"

DragonCut::DragonCut()
{
}

DragonCut::~DragonCut()
{
}

void DragonCut::Init()
{
	Attack::SetName("Dragon Cut");
	Attack::SetType("Dragon");
	Attack::SetPower(50);
	Attack::SetMaxPP(30);
	Attack::SetIdType(7);
	Attack::SetPP(30);
}

