#include "Chikorita.h"
#include "Bayleef.h"
#define hp 45
#define atk 49
#define def 65
#define speed 45

Chikorita::Chikorita()
{
	this->Init(64, 65);
	//
	this->m_name = "Chikorita";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Chikorita::~Chikorita()
{
}

Pokemon * Chikorita::Evolve()
{
	if (this->m_level >= 10)
	{
		return new Bayleef(this);
	}
	else
	{
		return nullptr;
	}
}