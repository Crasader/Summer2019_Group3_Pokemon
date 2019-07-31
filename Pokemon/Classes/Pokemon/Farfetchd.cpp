#include "Farfetchd.h"
#define hp 52
#define atk 45
#define def 55
#define speed 60

Farfetchd::Farfetchd()
{
}

Farfetchd::Farfetchd(int level) : Pokemon(level)
{
	this->Init(66, 67);
	//
	this->m_name = "Farfetchd";
	this->m_type = MyObject::TYPE_NORMAL;
	this->LearnSkill(new Tackle());
	this->LearnSkill(new QuickAttack());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Farfetchd::~Farfetchd()
{
}