#include "Ralts.h"
#include "Kirlia.h"
#define hp 35
#define atk 30
#define def 30
#define speed 40

Ralts::Ralts()
{
	this->Init(80, 81);
	//
	this->m_name = "Ralts";
	this->m_type = MyObject::TYPE_GRASS;
	this->LearnSkill(new LeechSeed());
	this->m_level = rand() % 2 + 1;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Ralts::~Ralts()
{
}

Pokemon * Ralts::Evolve()
{
	if (true)
	{
		this->LearnSkill(new EnergyBall());
		this->m_evolved = true;
		return new Kirlia(this);
	}
	else
	{
		return nullptr;
	}
}
