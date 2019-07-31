#include "Farfetchd.h"
#define hp 52
#define atk 45
#define def 55
#define speed 60

Farfetchd::Farfetchd()
{
	this->Init(66, 67);
	//
	this->m_name = "Farfetchd";
	this->m_type = MyObject::TYPE_NORMAL;
	this->LearnSkill(new Tackle());
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

Farfetchd::~Farfetchd()
{
}