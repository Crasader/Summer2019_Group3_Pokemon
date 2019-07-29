#include "RouteNPC.h"
#include "Pokemon.h"
#include "Pokemon\Pidgey.h"
#include "Pokemon\Ralts.h"
#include "Pokemon\Pikachu.h"


RouteNPC::RouteNPC()
{
	this->Init();
	m_state = true;
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

RouteNPC::~RouteNPC()
{
}

void RouteNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(123);
}

void RouteNPC::Update(float deltaTime)
{
}
