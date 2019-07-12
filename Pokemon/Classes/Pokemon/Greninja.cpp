#include "Greninja.h"
#define hp 72
#define atk 94
#define def 69
#define speed 122

Greninja::Greninja()
{
	this->Init(24, 25);
	//
	this->m_name = "Greninja";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Greninja::~Greninja()
{
}