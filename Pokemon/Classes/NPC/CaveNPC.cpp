#include "CaveNPC.h"
#include "Pokemon.h"
#include "Pokemon\Ponyta.h"
#include "Pokemon\Vulpix.h"
#include "Pokemon\Charmeleon.h"
CaveNPC::CaveNPC()
{
	this->Init();
	m_state = true;
	auto ponyta = new Ponyta();
	ponyta->SetLevel(10);
	this->m_pokemons.push_back(ponyta);

	auto vulpix = new Vulpix();
	vulpix->SetLevel(10);
	this->m_pokemons.push_back(vulpix);

	auto charmeleon = new Charmeleon();
	charmeleon->SetLevel(11);
	this->m_pokemons.push_back(charmeleon);
}

CaveNPC::~CaveNPC()
{
}

void CaveNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(92);
}

void CaveNPC::Update(float deltaTime)
{
}
