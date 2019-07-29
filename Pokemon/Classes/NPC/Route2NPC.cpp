#include "Route2NPC.h"
#include "Pokemon.h"
#include "Pokemon\Skymin.h"
#include "Pokemon\Flareon.h"
#include "Pokemon\Manectric.h"


Route2NPC::Route2NPC()
{
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

void Route2NPC::Update(float deltaTime)
{
}
