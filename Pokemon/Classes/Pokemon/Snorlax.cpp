#include "Snorlax.h"
#define hp 160
#define atk 80
#define def 75
#define speed 30

Snorlax::Snorlax()
{
	this->Init(44, 45);
	//
	this->m_name = "Snorlax";
	this->m_type = MyObject::TYPE_NORMAL;
	this->m_listSkill = { new Tackle(), new Thunderbolt(), nullptr };
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Snorlax::~Snorlax()
{
}