#include"WingAttack.h"

WingAttack::WingAttack()
{
}

WingAttack::~WingAttack()
{
}

void WingAttack::Init()
{
	Skill::SetName("Wing Attack");
	Skill::SetTypeName("Flying");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(10);
}