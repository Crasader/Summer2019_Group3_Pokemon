#include "CityNPC.h"
#include "Pokemon.h"
#include "Pokemon\Pidgey.h"
#include "Pokemon\Ralts.h"
#include "Pokemon\Pikachu.h"


CityNPC::CityNPC()
{
	auto pidgey = new Pidgey();
	pidgey->SetLevel(5);
	this->m_pokemons.push_back(pidgey);

	auto ralts = new Ralts();
	ralts->SetLevel(5);
	this->m_pokemons.push_back(ralts);

	auto pikachu = new Pikachu();
	pikachu->SetLevel(6);
	this->m_pokemons.push_back(pikachu);
}

CityNPC::~CityNPC()
{
}

void CityNPC::Update(float deltaTime)
{
}
