#include "LakeNPC.h"
#include "Pokemon.h"
#include "Pokemon\Charmander.h"
LakeNPC::LakeNPC(Layer * layer)
{
	this->Init();
	layer->addChild(this->m_spriteFront);

	auto charmender = new Charmander();
	charmender->SetLevel(9);
	this->m_pokemons.push_back(charmender);

	auto charmender2 = new Charmander();
	charmender2->SetLevel(9);
	this->m_pokemons.push_back(charmender2);

	auto charmender3 = new Charmander();
	charmender3->SetLevel(9);
	this->m_pokemons.push_back(charmender3);

	auto charmender4 = new Charmander();
	charmender4->SetLevel(9);
	this->m_pokemons.push_back(charmender4);

	auto charmender5 = new Charmander();
	charmender5->SetLevel(9);
	this->m_pokemons.push_back(charmender5);

	auto charmender6 = new Charmander();
	charmender6->SetLevel(9);
	this->m_pokemons.push_back(charmender6);
}

LakeNPC::~LakeNPC()
{
}

void LakeNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(46);
}

void LakeNPC::Update(float deltaTime)
{
}
