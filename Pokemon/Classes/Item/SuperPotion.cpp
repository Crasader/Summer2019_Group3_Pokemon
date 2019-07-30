#include "SuperPotion.h"

SuperPotion::SuperPotion()
{
	this->Init(138);
	this->m_id = 1;
	this->m_gold = 10;
	this->hpRevice = 100;
	this->m_name = "Super Potion";
	this->m_number = 1;
	this->m_describe = "Restores 100 HP.";
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