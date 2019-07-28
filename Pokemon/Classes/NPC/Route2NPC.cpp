#include "Route2NPC.h"
#include "Pokemon.h"
#include "Pokemon\Skymin.h"
#include "Pokemon\Flareon.h"
#include "Pokemon\Manectric.h"


Route2NPC::Route2NPC()
{
	this->Init();
	m_state = true;
	auto skymin = new Skymin();
	skymin->SetLevel(10);
	this->m_pokemons.push_back(skymin);

	auto flareon = new Flareon();
	flareon->SetLevel(10);
	this->m_pokemons.push_back(flareon);

	auto manectric = new Manectric();
	manectric->SetLevel(11);
	this->m_pokemons.push_back(manectric);
}

Route2NPC::~Route2NPC()
{
}

void Route2NPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(94);
}

void Route2NPC::Update(float deltaTime)
{
}
