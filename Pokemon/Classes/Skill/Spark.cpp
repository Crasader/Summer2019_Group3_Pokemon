#include "Spark.h"

Spark::Spark()
{
	this->Init();
}

Spark::~Spark()
{
}

void Spark::Init()
{
	this->AddAnimation(108);
	this->SetScale(3);
	Skill::SetName("Spark");
	Skill::SetTypeName("Electric");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_ELECTRIC);
	Skill::SetCurrentPP(20);
}