#include "Meganium.h"
#define hp 80
#define atk 82
#define def 100
#define speed 80

Meganium::Meganium(Bayleef* it)
{
	this->Init(72, 73);
	//
	this->m_name = "Meganium";
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

Meganium::~Meganium()
{
}