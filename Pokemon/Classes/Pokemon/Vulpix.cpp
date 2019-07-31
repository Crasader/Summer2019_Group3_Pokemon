#include "Vulpix.h"
#define hp 40
#define atk 40
#define def 40
#define speed 65

Vulpix::Vulpix()
{
	this->Init(54, 55);
	//
	this->m_name = "Vulpix";
	this->m_type = MyObject::TYPE_FIRE;
	this->LearnSkill(new Scratch());
	this->LearnSkill(new Ember());
	this->m_level = rand() % 3 + 3;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Vulpix::~Vulpix()
{
}