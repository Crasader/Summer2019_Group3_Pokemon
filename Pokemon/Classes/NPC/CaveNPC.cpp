#include "CaveNPC.h"
#include "Pokemon.h"
#include "Pokemon\Snorlax.h"
#include "Pokemon\Vulpix.h"
#include "Pokemon\Charmeleon.h"
CaveNPC::CaveNPC()
{
	this->Init();
	auto snorlax = new Snorlax(10);
	this->m_pokemons.push_back(snorlax);
}

CaveNPC::~CaveNPC()
{
}

void CaveNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(125);
}

void CaveNPC::Update(float deltaTime)
{
}

vector<Pokemon*> CaveNPC::GetListPokemon()
{
	return this->m_pokemons;
}