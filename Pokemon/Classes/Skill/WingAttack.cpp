#include"WingAttack.h"

WingAttack::WingAttack()
{
	this->Init();
}

WingAttack::~WingAttack()
{
}

void WingAttack::Init()
{
	Attack::SetName("Wing Attack");
	Attack::SetType("Flying");
	Attack::SetPower(80);
	Attack::SetMaxPP(10);
	Attack::SetIdType(6);
	Attack::SetPP(10);
}

