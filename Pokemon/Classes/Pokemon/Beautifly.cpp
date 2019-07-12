#include "Beautifly.h"
#define hp 60
#define atk 85
#define def 50
#define speed 65

Beautifly::Beautifly()
{
	this->Init(60, 61);
	//
	this->m_name = "Beautifly";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Beautifly::~Beautifly()
{
}