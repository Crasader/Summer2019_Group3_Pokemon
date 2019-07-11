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
	Attack::SetName("Draco Meteor");
	Attack::SetType("Dragon");
	Attack::SetPower(120);
	Attack::SetMaxPP(5);
	Attack::SetIdType(7);
	Attack::SetPP(5);
}

