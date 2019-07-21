#include"BodySlam.h"

BodySlam::BodySlam()
{
}

BodySlam::~BodySlam()
{
}

void BodySlam::Init()
{
	Skill::SetName("Body Slam");
	Skill::SetTypeName("Normal");
	Skill::SetPower(90);
	Skill::SetMaxPP(10);
	Skill::SetIdType(1);
	Skill::SetCurrentPP(10);
}

