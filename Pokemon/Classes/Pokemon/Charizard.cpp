#include "Charizard.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65

Charizard::Charizard()
{
}

Charizard::Charizard(Charmeleon * it)
{
	this->Init(2, 3);
	//
	this->m_name = "Charizard";
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

Charizard::~Charizard()
{
}