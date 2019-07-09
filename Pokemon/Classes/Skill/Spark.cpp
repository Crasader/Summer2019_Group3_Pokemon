#include"Spark.h"

Spark::Spark()
{
}

Spark::~Spark()
{
}

void Spark::Init()
{
	Attack::SetName("Spark");
	Attack::SetType("Electric");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(5);
	Attack::SetPP(20);
}

