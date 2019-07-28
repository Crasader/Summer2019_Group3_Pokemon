#include "Bayleef.h"
#include "Meganium.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65

Bayleef::Bayleef(Chikorita* it)
{
	this->Init(58, 59);
	//
	this->m_name = "Bayleef";
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

Bayleef::~Bayleef()
{
}

Pokemon * Bayleef::Evolve()
{
	if (this->m_level >= 15)
	{
		this->m_evolved = true;
		return new Meganium(this);
	}
	else
	{
		return nullptr;
	}
}
