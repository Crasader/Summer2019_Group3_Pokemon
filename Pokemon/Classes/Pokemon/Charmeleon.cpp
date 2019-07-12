#include "Charmeleon.h"
#include "Charizard.h"
#define hp 58
#define atk 72
#define def 62
#define speed 80

Charmeleon::Charmeleon()
{
}

Charmeleon::Charmeleon(Charmander * it)
{
	this->Init(6, 7);
	//
	this->m_name = "Charmeleon";
	this->m_level = it->GetLevel();
	this->m_maxHealth = it->GetMaxHP() + 15;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = it->GetAtk() + 5;
	this->m_defense = it->GetDef() + 5;
	this->m_attackSpeed = it->GetAtkSpeed() + 2;
	this->m_currentExp = 0;
	this->m_maxExp = it->GetMaxExp();
	delete it;
}

Charmeleon::~Charmeleon()
{
}

Pokemon * Charmeleon::Evolve()
{
	if (this->m_level >= 15)
	{
		return new Charizard(this);
	}
	else
	{
		return nullptr;
	}
}