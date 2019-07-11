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
	Skill::SetType("Electric");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(5);
	Skill::SetPP(20);
}

