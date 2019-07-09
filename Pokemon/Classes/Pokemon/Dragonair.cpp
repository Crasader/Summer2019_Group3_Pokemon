#include "Dragonair.h"
#include "Dragonite.h"
#define hp 61
#define atk 84
#define def 65
#define speed 70

Dragonair::Dragonair()
{
	this->Init(8, 9);
	//
	this->m_name = "Dragonair";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Dragonair::~Dragonair()
{
}

Pokemon * Dragonair::Evolve()
{
	if (true)
	{
		return new Dragonite(this);
	}
	else
	{
		return nullptr;
	}
}
