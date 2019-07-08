#include "CityNPC.h"
#include "Pokemon.h"
#include "Pokemon\Charmander.h"
CityNPC::CityNPC(Scene * scene)
{
	this->Init();
	auto charmender = new Charmander();
	this->m_pokemons.push_back(charmender);
	// set power of pokemon
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

CityNPC::~CityNPC()
{
}

void CityNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void CityNPC::Update(float deltaTime)
{
}
