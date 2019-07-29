#include "RoadNPC.h"
#include "Pokemon.h"
#include "Pokemon\Kirlia.h"
#include "Pokemon\Snorlax.h"
#include "Pokemon\Pidgeot.h"


RoadNPC::RoadNPC()
{
	auto kirlia = new Kirlia();
	kirlia->SetLevel(14);
	this->m_pokemons.push_back(kirlia);

	auto snorlax = new Snorlax();
	snorlax->SetLevel(14);
	this->m_pokemons.push_back(snorlax);

	auto pidgeot = new Pidgeot();
	pidgeot->SetLevel(15);
	this->m_pokemons.push_back(pidgeot);
}

RoadNPC::~RoadNPC()
{
}

void RoadNPC::Update(float deltaTime)
{
}
