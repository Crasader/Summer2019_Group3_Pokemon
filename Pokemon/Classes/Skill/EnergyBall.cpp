#include"EnergyBall.h"

EnergyBall::EnergyBall()
{
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::Init()
{
	Attack::SetName("Energy Ball");
	Attack::SetType("Grass");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(4);
	Attack::SetPP(10);
}

