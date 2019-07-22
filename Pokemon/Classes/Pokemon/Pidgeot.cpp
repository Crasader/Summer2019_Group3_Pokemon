#include "Pidgeot.h"
#define hp 83
#define atk 80
#define def 75
#define speed 101

Pidgeot::Pidgeot()
{
}

Pidgeot::Pidgeot(Pidgeotto * it)
{
	this->Init(74, 75);
	//
	this->m_name = "Pidgeot";
	this->m_type = it->GetType();
	this->m_skills = { it->GetSkillById(0), it->GetSkillById(1), it->GetSkillById(2) };
	this->m_level = it->GetLevel();
	this->m_maxHealth = it->GetMaxHP() + 15;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = it->GetAtk() + 5;
	this->m_defense = it->GetDef() + 5;
	this->m_attackSpeed = it->GetAtkSpeed() + 2;
	this->m_currentExp = 0;
	this->m_maxExp = it->GetMaxExp();
	delete it;
}

Pidgeot::~Pidgeot()
{
}