#include "Revive.h"
#include "Pokemon.h"

Revive::Revive()
{
	this->Init(109);
	this->name = "Revive";
	this->gold = 20;
	this->Number = 0;
}

Revive::~Revive()
{
}

void Revive::ReviceHealth(Pokemon * pokemon)
{
	// nếu mạng = false
	// set mạng = true
	pokemon->SetCurrentHP(pokemon->GetMaxHP() / 2);
}
