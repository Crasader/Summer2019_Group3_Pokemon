#include "Route2NPC.h"
#include "Pokemon.h"
#include "Pokemon\Skymin.h"
#include "Pokemon\Ponyta.h"
#include "Pokemon\Manectric.h"


Route2NPC::Route2NPC()
{
	this->Init();
	auto skymin = new Skymin(10);
	this->m_pokemons.push_back(skymin);

	auto ponyta = new Ponyta(10);
	this->m_pokemons.push_back(ponyta);

	auto manectric = new Manectric(11);
	this->m_pokemons.push_back(manectric);
}

Route2NPC::~Route2NPC()
{
}

void Route2NPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(128);
}

void Route2NPC::Update(float deltaTime)
{
}

vector<Pokemon*> Route2NPC::GetListPokemon()
{
	return this->m_pokemons;
}
