#include "MaxPotion.h"

MaxPotion::MaxPotion()
{
	this->Init(139);
	this->m_id = 2;
	this->m_gold = 30;
	this->m_name = "Max Potion";
	this->m_number = 0;
	this->m_describe = "Fully restores HP.";
}

MaxPotion::~MaxPotion()
{
}

void MaxPotion::ReviceHealthPokemon(Pokemon * pokemon)
{
	pokemon->SetCurrentHP(pokemon->GetMaxHP());
	this->m_number--;
}