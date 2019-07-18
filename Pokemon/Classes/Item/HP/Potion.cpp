#include "Potion.h"

Potion::Potion()
{
	this->Init(106);
	this->name = "Posion";
	this->gold = 5;
	this->Number = 0;

}

Potion::~Potion()
{
}

void Potion::ReviceHealth(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetCurrentHP() + 50);
	if (pokemon->GetCurrentHP() > pokemon->GetMaxHP())
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP());
	}
}
