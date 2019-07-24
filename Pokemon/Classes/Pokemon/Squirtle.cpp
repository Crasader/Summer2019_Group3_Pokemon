#include "Squirtle.h"
#include "Wartortle.h"
#define hp 44
#define atk 48
#define def 65
#define speed 43

Squirtle::Squirtle()
{
	this->Init(46, 47);
	//
	this->m_name = "Squirtle";
	this->m_type = MyObject::TYPE_WATER;
	this->m_listSkill = { new WaterGun(), new WaterPulse(), nullptr };
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Squirtle::~Squirtle()
{
}

Pokemon * Squirtle::Evolve()
{
	if (this->m_level >= 10)
	{
		return new Wartortle(this);
	}
	else
	{
		return nullptr;
	}
}