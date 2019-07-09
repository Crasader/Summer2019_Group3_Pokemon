#include "Celebi.h"
#define hp 100
#define atk 100
#define def 100
#define speed 100

Celebi::Celebi()
{
	this->Init(62, 63);
	//
	this->m_name = "Celebi";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Celebi::~Celebi()
{
}