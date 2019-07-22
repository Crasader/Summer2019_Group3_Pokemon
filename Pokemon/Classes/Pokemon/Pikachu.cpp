#include "Pikachu.h"
#define hp 38
#define atk 55
#define def 40
#define speed 90

Pikachu::Pikachu()
{
	this->Init(36, 37);
	//
	this->m_name = "Pikachu";
	this->m_type = MyObject::TYPE_ELECTRIC;
	this->m_skills = { new Tackle(), new Thunder(), nullptr };
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Pikachu::~Pikachu()
{
}