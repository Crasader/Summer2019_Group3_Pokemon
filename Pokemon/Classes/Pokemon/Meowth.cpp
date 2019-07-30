#include "Meowth.h"
#define hp 40
#define atk 45
#define def 35
#define speed 90

Meowth::Meowth()
{
	this->Init(32, 33);
	//
	this->m_name = "Meowth";
	this->m_type = MyObject::TYPE_NORMAL;
	this->LearnSkill(new Scratch());
	this->LearnSkill(new QuickAttack());
	this->m_level = rand() % 2 + 1;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Meowth::~Meowth()
{
}