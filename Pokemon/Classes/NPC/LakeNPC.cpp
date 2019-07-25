#include "LakeNPC.h"
#include "Pokemon.h"
#include "Pokemon\Feebas.h"
#include "Pokemon\Vaporeon.h"
#include "Pokemon\Wartortle.h"
LakeNPC::LakeNPC()
{
	this->Init();
	m_state = true;
	auto feebas = new Feebas();
	feebas->SetLevel(10);
	this->m_pokemons.push_back(feebas);

	auto vaporeon = new Vaporeon();
	vaporeon->SetLevel(10);
	this->m_pokemons.push_back(vaporeon);

	auto wartortle = new Wartortle();
	wartortle->SetLevel(11);
	this->m_pokemons.push_back(wartortle);
}

LakeNPC::~LakeNPC()
{
}

void LakeNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(98);
}

void LakeNPC::Update(float deltaTime)
{
}
