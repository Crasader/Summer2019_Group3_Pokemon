#include "ChampionNPC.h"
#include "Pokemon.h"
#include "Pokemon\Dragonite.h"
#include "Pokemon\Garchomp.h"
#include "Pokemon\Salamence.h"
#include "Pokemon\Greninja.h"
#include "Pokemon\Charizard.h"
#include "Pokemon\Blastoise.h"
ChampionNPC::ChampionNPC()
{
	this->Init();
	m_state = true;

	auto blastoise = new Blastoise();
	blastoise->SetLevel(20);
	this->m_pokemons.push_back(blastoise);

	auto greninja = new Greninja();
	greninja->SetLevel(20);
	this->m_pokemons.push_back(greninja);

	auto charizard = new Charizard();
	charizard->SetLevel(20);
	this->m_pokemons.push_back(charizard);

	auto dragonite = new Dragonite();
	dragonite->SetLevel(20);
	this->m_pokemons.push_back(dragonite);

	auto garchomp = new Garchomp();
	garchomp->SetLevel(20);
	this->m_pokemons.push_back(garchomp);

	auto salamence = new Salamence();
	salamence->SetLevel(20);
	this->m_pokemons.push_back(salamence);
}

ChampionNPC::~ChampionNPC()
{
}

void ChampionNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(46);
}

void ChampionNPC::Update(float deltaTime)
{
}
