#include "SuperPotion.h"

SuperPotion::SuperPotion()
{
	this->m_id = 1;
	this->m_gold = 10;
	this->hpRevice = 50;
	this->m_name = "Super Potion";
	this->Init(138);
	this->m_number = 1;
}

SuperPotion::~SuperPotion()
{
}


void SuperPotion::ReviceHealthPokemon(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetCurrentHP() + this->hpRevice);
	if (pokemon->GetCurrentHP() > pokemon->GetMaxHP())
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP());
	}
}
