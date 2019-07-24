#include "Manectric.h"
#define hp 70
#define atk 75
#define def 60
#define speed 105

Manectric::Manectric()
{
}

Manectric::Manectric(Electrike * it)
{
	this->Init(30, 31);
	//
	this->m_name = "Manectric";
	this->m_type = it->GetType();
	this->m_listSkill = { it->GetSkillById(0), it->GetSkillById(1), it->GetSkillById(2) };
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

Manectric::~Manectric()
{
}