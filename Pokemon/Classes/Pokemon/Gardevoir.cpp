#include "Gardevoir.h"
#define hp 68
#define atk 95
#define def 90
#define speed 80

Gardevoir::Gardevoir()
{
}

Gardevoir::Gardevoir(Kirlia * it)
{
	this->Init(68, 69);
	//
	this->m_name = "Gardevoir";
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

Gardevoir::~Gardevoir()
{
}