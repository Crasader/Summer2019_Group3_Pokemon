#include "Dragonite.h"
#define hp 91
#define atk 134
#define def 95
#define speed 80

Dragonite::Dragonite()
{
}

Dragonite::Dragonite(Dragonair * it)
{
	this->Init(10, 11);
	//
	this->m_name = "Dragonite";
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

Dragonite::~Dragonite()
{
}