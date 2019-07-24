#include "Garchomp.h"
#define hp 100
#define atk 89
#define def 67
#define speed 86

Garchomp::Garchomp()
{
	this->Init(22, 23);
	//
	this->m_name = "Garchomp";
	this->m_type = MyObject::TYPE_DRAGON;
	this->m_listSkill = { new DragonCut(), new DragonClaw(), nullptr };
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Garchomp::~Garchomp()
{
}