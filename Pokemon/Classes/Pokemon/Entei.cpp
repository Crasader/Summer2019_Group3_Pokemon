#include "Entei.h"
#define hp 115
#define atk 102
#define def 80
#define speed 100

Entei::Entei()
{
	this->Init(16, 17);
	//
	this->m_name = "Entei";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Entei::~Entei()
{
}