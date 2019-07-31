#include "Ponyta.h"
#define hp 50
#define atk 50
#define def 55
#define speed 90

Ponyta::Ponyta()
{
	this->Init(38, 39);
	//
	this->m_name = "Ponyta";
	this->m_type = MyObject::TYPE_FIRE;
	this->LearnSkill(new Ember());
	this->LearnSkill(new FirePunch());
	this->m_level = rand() % 3 + 3;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Ponyta::~Ponyta()
{
}