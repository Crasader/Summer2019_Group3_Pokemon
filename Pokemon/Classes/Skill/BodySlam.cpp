#include"BodySlam.h"

BodySlam::BodySlam()
{
	this->Init();
}

BodySlam::~BodySlam()
{
}

void BodySlam::Init()
{
	Attack::SetName("Body Slam");
	Attack::SetType("Normal");
	Attack::SetPower(90);
	Attack::SetMaxPP(10);
	Attack::SetIdType(1);
	Attack::SetPP(10);
}

