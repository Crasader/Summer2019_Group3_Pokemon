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
	Skill::SetName("Body Slam");
	Skill::SetType("Normal");
	Skill::SetPower(90);
	Skill::SetMaxPP(10);
	Skill::SetIdType(1);
	Skill::SetPP(10);
}

