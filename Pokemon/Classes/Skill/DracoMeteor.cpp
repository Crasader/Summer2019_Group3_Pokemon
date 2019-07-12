#include"DracoMeteor.h"

DracoMeteor::DracoMeteor()
{
	this->Init();
}

DracoMeteor::~DracoMeteor()
{
}

void DracoMeteor::Init()
{
	Skill::SetName("Draco Meteor");
	Skill::SetType("Dragon");
	Skill::SetPower(120);
	Skill::SetMaxPP(5);
	Skill::SetIdType(7);
	Skill::SetPP(5);
}

