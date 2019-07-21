#include "PP.h"

PP::PP()
{
	this->Number = 0;
	this->gold = 10;
	this->name = "PP";
}

PP::~PP()
{
}

void PP::ReviceSkill(Attack * skill)
{
	skill->SetPP(skill->GetMaxPP());
}
