#include "Blastoise.h"
#define hp 79
#define atk 84
#define def 103
#define speed 78

Blastoise::Blastoise()
{
	this->Init(0, 1);
}

Blastoise::Blastoise(Wartortle * it)
{
	this->Init(0, 1);
	//
	this->m_name = "Blastoise";
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

Blastoise::~Blastoise()
{
}