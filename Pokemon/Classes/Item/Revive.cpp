#include "Revive.h"

Revive::Revive()
{
	this->Init(141);
	this->m_id = 4;
	this->m_gold = 20;
	this->m_number = 999;
	this->m_name = "Revive";
	this->m_describe = "A medicine that revives a fainted Pokemon. It restores half the Pokemon's maximum HP.";
}

Revive::~Revive()
{
}

void Revive::RevivePokemon(Pokemon * pokemon)
{
	pokemon->SetState(1);
	pokemon->SetCurrentHP(pokemon->GetMaxHP() / 2);
}