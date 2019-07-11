#include"RazorLeaf.h"

RazorLeaf::RazorLeaf()
{
	this->Init();
}

RazorLeaf::~RazorLeaf()
{
}

void RazorLeaf::Init()
{
	Attack::SetName("Razor Leaf");
	Attack::SetType("Grass");
	Attack::SetPower(60);
	Attack::SetMaxPP(20);
	Attack::SetIdType(4);
	Attack::SetPP(20);
}

