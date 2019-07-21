#include "MaxRevive.h"
#include "Pokemon.h"
MaxRevive::MaxRevive()
{
	this->Init(109);
	this->name = "Revive";
	this->gold = 20;
	this->Number = 0;
}

MaxRevive::~MaxRevive()
{
}

void MaxRevive::ReviceHealth(Pokemon * pokemon)
{
	// nếu mạng = false
	// set mạng = true
	pokemon->SetCurrentHP(pokemon->GetMaxHP());
}
