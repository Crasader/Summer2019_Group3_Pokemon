#include "Meowth.h"
#define hp 40
#define atk 42
#define def 38
#define speed 90

Meowth::Meowth()
{
	this->Init(32, 33);
	//
	this->m_name = "Meowth";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Meowth::~Meowth()
{
}