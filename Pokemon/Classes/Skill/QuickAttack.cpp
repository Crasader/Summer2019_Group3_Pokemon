#include"QuickAttack.h"

QuickAttack::QuickAttack()
{
	this->Init();
}

QuickAttack::~QuickAttack()
{
}

void QuickAttack::Init()
{
	Attack::SetName("Quick Attack");
	Attack::SetType("Normal");
	Attack::SetPower(50);
	Attack::SetMaxPP(20);
	Attack::SetIdType(1);
	Attack::SetPP(20);
}

