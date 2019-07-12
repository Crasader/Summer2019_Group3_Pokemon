#include "SuperPotion.h"

SuperPotion::SuperPotion()
{
	this->Init(107);
	this->name = "Posion";
	this->gold = 10;
}

SuperPotion::~SuperPotion()
{
}

void SuperPotion::ReviceHealth(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetCurrentHP() + 100);
	if (pokemon->GetCurrentHP() > pokemon->GetMaxHP())
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP());
	}
}
