#include "Milotic.h"
#define hp 95
#define atk 60
#define def 79
#define speed 81

Milotic::Milotic()
{
}

Milotic::Milotic(Feebas * it)
{
	this->Init(34, 35);
	//
	this->m_name = "Milotic";
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

Milotic::~Milotic()
{
}