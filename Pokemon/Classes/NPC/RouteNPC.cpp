#include "RouteNPC.h"
#include "Pokemon.h"
#include "Pokemon\Charmander.h"
RouteNPC::RouteNPC(Scene * scene)
{
	this->Init();
	auto charmender = new Charmander();
	this->m_pokemons.push_back(charmender);
	// set power of pokemon
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

RouteNPC::~RouteNPC()
{
}

void RouteNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void RouteNPC::Update(float deltaTime)
{
}
