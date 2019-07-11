#include"RazorLeaf.h"

RazorLeaf::RazorLeaf()
{
}

RazorLeaf::~RazorLeaf()
{
}

void RazorLeaf::Init()
{
	Skill::SetName("Razor Leaf");
	Skill::SetType("Grass");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(4);
	Skill::SetPP(20);
}

