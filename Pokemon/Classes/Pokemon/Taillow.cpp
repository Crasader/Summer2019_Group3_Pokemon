#include "Taillow.h"
#include "Swellow.h"
#define hp 40
#define atk 55
#define def 30
#define speed 85

Taillow::Taillow()
{
	this->Init(88, 89);
	//
	this->m_name = "Taillow";
	this->m_type = MyObject::TYPE_FLYING;
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Taillow::~Taillow()
{
}

Pokemon * Taillow::Evolve()
{
	if (this->m_level >= 10)
	{
		this->m_evolved = true;
		return new Swellow(this);
	}
	else
	{
		return nullptr;
	}
}