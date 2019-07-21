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
	Skill::SetIdType(5);
	Skill::SetCurrentPP(20);
}

