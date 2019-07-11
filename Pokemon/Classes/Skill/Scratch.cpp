#include"Scratch.h"

Scratch::Scratch()
{
	this->Init();
}

Scratch::~Scratch()
{
}

void Scratch::Init()
{
	Attack::SetName("Scratch");
	Attack::SetType("Normal");
	Attack::SetPower(60);
	Attack::SetMaxPP(15);
	Attack::SetIdType(1);
	Attack::SetPP(10);
}

