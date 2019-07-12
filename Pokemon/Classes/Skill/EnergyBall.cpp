#include"EnergyBall.h"

EnergyBall::EnergyBall()
{
	this->Init();
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::Init()
{
	Skill::SetName("Energy Ball");
	Skill::SetType("Grass");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(4);
	Skill::SetPP(10);
}

