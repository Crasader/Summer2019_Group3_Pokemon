#include "Raikou.h"
#define hp 90
#define atk 85
#define def 75
#define speed 115

Raikou::Raikou()
{
	this->Init(40, 41);
	//
	this->m_name = "Raikou";
	this->m_type = MyObject::TYPE_ELECTRIC;
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

Raikou::~Raikou()
{
}