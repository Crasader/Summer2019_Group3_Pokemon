#include "Electrike.h"
#include "Manectric.h"
#define hp 40
#define atk 55
#define def 40
#define speed 65

Electrike::Electrike()
{
	this->Init(14, 15);
	//
	this->m_name = "Electrike";
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Electrike::~Electrike()
{
}

Pokemon * Electrike::Evolve()
{
	if (true)
	{
		return new Manectric(this);
	}
	else
	{
		return nullptr;
	}
}
