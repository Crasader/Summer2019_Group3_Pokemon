#include"DracoMeteor.h"

DracoMeteor::DracoMeteor()
{
}

DracoMeteor::~DracoMeteor()
{
}

void DracoMeteor::Init()
{
	Skill::SetName("Draco Meteor");
	Skill::SetTypeName("Dragon");
	Skill::SetPower(120);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_DRAGON);
	Skill::SetCurrentPP(5);
}

