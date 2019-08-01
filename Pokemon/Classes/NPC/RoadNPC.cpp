#include "RoadNPC.h"
#include "Pokemon.h"
#include "Pokemon\Kirlia.h"
#include "Pokemon\Snorlax.h"
#include "Pokemon\Pidgeot.h"


RoadNPC::RoadNPC()
{
	this->Init();
	auto kirlia = new Kirlia(14);
	this->m_pokemons.push_back(kirlia);

	auto snorlax = new Snorlax(14);
	this->m_pokemons.push_back(snorlax);

	auto pidgeot = new Pidgeotto(14);
	this->m_pokemons.push_back(pidgeot);
}

RoadNPC::~RoadNPC()
{
}

void RoadNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(129);
}

void RoadNPC::Update(float deltaTime)
{
}

vector<Pokemon*> RoadNPC::GetListPokemon()
{
	return this->m_pokemons;
}