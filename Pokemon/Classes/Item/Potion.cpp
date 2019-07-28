#include "Potion.h"

Potion::Potion()
{
	this->Init(137);
	this->m_id = 0;
	this->m_gold = 5;
	this->hpRevice = 20;
	this->m_name = "Potion";
	this->m_number = 5;
}

Potion::~Potion()
{
}

void Potion::ReviceHealthPokemon(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetCurrentHP() + this->hpRevice);
	if (pokemon->GetCurrentHP() > pokemon->GetMaxHP())
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP());
	}
}