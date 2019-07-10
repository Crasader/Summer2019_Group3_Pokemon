#include "Garchomp.h"
#define hp 58
#define atk 70
#define def 45
#define speed 42

Garchomp::Garchomp()
{
	this->Init(22, 23);
	//
	this->m_name = "Garchomp";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Garchomp::~Garchomp()
{
}