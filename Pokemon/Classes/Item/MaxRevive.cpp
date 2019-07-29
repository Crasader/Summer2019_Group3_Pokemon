#include "MaxRevive.h"

MaxRevive::MaxRevive()
{
	this->Init(142);
	this->m_id = 5;
	this->m_gold = 50;
	this->m_number = 0;
	this->m_name = "Max Revive";
	this->m_describe = "Revives a Pokémon full HP";
}

MaxRevive::~MaxRevive()
{
}

void MaxRevive::MaxRevivePokemon(Pokemon * pokemon)
{
	pokemon->SetState(1);
	pokemon->SetCurrentHP(pokemon->GetMaxHP());
}