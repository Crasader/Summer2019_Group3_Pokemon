#include "MaxPotion.h"

MaxPotion::MaxPotion()
{
	this->m_id = 2;
	this->m_gold = 30;
	this->m_name = "Max Potion";
	this->Init(139);
	this->m_number = 0;
}

MaxPotion::~MaxPotion()
{
}


void MaxPotion::ReviceHealthPokemon(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetMaxHP());
}
