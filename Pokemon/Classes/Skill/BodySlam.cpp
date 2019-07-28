#include "BodySlam.h"

BodySlam::BodySlam()
{
	this->Init();
}

BodySlam::~BodySlam()
{
}

void BodySlam::Init()
{
	this->AddAnimation(92);
	Skill::SetName("Body Slam");
	Skill::SetTypeName("Normal");
	Skill::SetPower(90);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_NORMAL);
	Skill::SetCurrentPP(10);
}