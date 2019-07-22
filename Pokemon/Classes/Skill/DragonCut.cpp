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
	this->AddAnimation(96);
	this->SetScale(2);
	Skill::SetName("Dragon Cut");
	Skill::SetTypeName("Dragon");
	Skill::SetPower(50);
	Skill::SetMaxPP(30);
	Skill::SetIdType(MyObject::TYPE_DRAGON);
	Skill::SetCurrentPP(30);
}