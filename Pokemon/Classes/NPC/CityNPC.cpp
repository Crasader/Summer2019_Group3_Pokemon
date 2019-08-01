#include "CityNPC.h"
#include "Pokemon.h"
#include "include_pokemon.h"


CityNPC::CityNPC()
{
	auto ponyta = new Ponyta(8);
	this->m_pokemons.push_back(ponyta);

	auto shaymin = new Shaymin(8);
	this->m_pokemons.push_back(shaymin);

	auto pikachu = new Kirlia(10);
	this->m_pokemons.push_back(pikachu);
}

CityNPC::~CityNPC()
{
}

void CityNPC::Update(float deltaTime)
{
}
