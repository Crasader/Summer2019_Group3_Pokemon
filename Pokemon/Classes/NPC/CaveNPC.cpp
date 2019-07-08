#include "CaveNPC.h"
#include "Pokemon.h"
#include "Pokemon\Charmander.h"
CaveNPC::CaveNPC(Scene * scene)
{
	this->Init();
	auto charmender = new Charmander();
	this->m_pokemons.push_back(charmender);
	// set power of pokemon
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

CaveNPC::~CaveNPC()
{
}

void CaveNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void CaveNPC::Update(float deltaTime)
{
}
