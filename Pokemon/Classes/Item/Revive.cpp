#include "Revive.h"

Revive::Revive()
{
	this->m_id = 4;
	this->m_gold = 20;
	this->m_number = 1;
	this->m_name = "Revive";
	this->Init(141);
}

Revive::~Revive()
{
}

void Revive::RevivePokemon(Pokemon * pokemon)
{
	pokemon->SetState(1);
	pokemon->SetCurrentHP(pokemon->GetMaxHP() / 2);
}
