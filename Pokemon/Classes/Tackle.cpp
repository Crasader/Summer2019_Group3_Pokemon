#include"Tackle.h"

Tackle::Tackle()
{
}

Tackle::~Tackle()
{
}

string Tackle::GetName()
{
	return name;
}

string Tackle::GetType()
{
	return type;
}

void Tackle::Init()
{
	SetName("Tackle");
	SetType("Normal");
	Attack::getAnimate(0);
	Attack::SetPower(40);
	Attack::SetPP(35);
}

void Tackle::SetName(string n)
{
	name = n;
}

void Tackle::SetType(string t)
{
	type = t;
}
