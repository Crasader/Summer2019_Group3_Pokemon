#include"DragonCut.h"

DragonCut::DragonCut()
{
	this->Init();
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

