#include"Spark.h"

Spark::Spark()
{
}

Spark::~Spark()
{
}

void Spark::Init()
{
	Skill::SetName("Spark");
	Skill::SetTypeName("Electric");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_ELECTRIC);
	Skill::SetCurrentPP(20);
}

