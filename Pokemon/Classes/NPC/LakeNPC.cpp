#include "LakeNPC.h"
#include "Pokemon.h"
#include "Pokemon\Feebas.h"
#include "Pokemon\Shaymin.h"
#include "Pokemon\Wartortle.h"

LakeNPC::LakeNPC()
{
	this->Init();
	auto feebas = new Feebas(10);
	this->m_pokemons.push_back(feebas);

	auto shaymin = new Shaymin(10);
	this->m_pokemons.push_back(shaymin);

	auto wartortle = new Wartortle(11);
	this->m_pokemons.push_back(wartortle);
}

LakeNPC::~LakeNPC()
{
}

void LakeNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(124);
}

void LakeNPC::Update(float deltaTime)
{
}

vector<Pokemon*> LakeNPC::GetListPokemon()
{
	return this->m_pokemons;
}